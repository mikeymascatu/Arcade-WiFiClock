#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ShiftDisplay2.h>

// Pin mappings/display settings on the Hack Hour Clock
ShiftDisplay2 display(9, 10, 11, COMMON_CATHODE, 4);

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "PASS";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Time variables
unsigned long epochTime;
String formattedTime;
int currentHour;
int currentMinute;
int currentSecond;

String displayHours, displayMinutes;
String displayTime;
String displaySpacer;

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);
  
  // Attempt to connect to Wi-Fi network
  display.set("SYNC");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  display.show(4000);


  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
 }
  Serial.println();
  Serial.println("Connected to WiFi");


  // Initialize the NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(0); // Set time offset if necessary
}

void loop() {
  // Update the time from the NTP server
  timeClient.update();

  // Get the epoch time
  epochTime = timeClient.getEpochTime();

  // Calculate hours, minutes, and seconds from epoch time
  currentHour = ((epochTime % 86400L) / 3600) - 4; // account for EST
  currentMinute = (epochTime % 3600) / 60;
  currentSecond = epochTime % 60;
  
  if (currentHour > 12){
    currentHour = currentHour - 12; 
  }
  
  displayHours = String(currentHour);
  displayMinutes = String(currentMinute);
  displaySpacer = String("0");
  if (currentMinute < 10){
    displayTime = displayHours += displaySpacer += displayMinutes;
  } else{
    displayTime = displayHours += displayMinutes;
  }

  // Print the current time
  Serial.print("Current time: ");
  Serial.print(currentHour);
  Serial.print(":");
  if (currentMinute < 10) {
    Serial.print("0");
  }
  Serial.print(currentMinute);
  Serial.print(":");
  if (currentSecond < 10) {
    Serial.print("0");
  }
  Serial.println(currentSecond);

  display.set(displayTime, ALIGN_RIGHT);
  display.changeDot(1);
  display.show(1000);

  // Wait for 10 seconds before the next update
  delay(100);
}

