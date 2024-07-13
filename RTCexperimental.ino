#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ShiftDisplay2.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"

// Pin mappings/display settings on the Hack Hour Clock
ShiftDisplay2 display(9, 10, 11, COMMON_CATHODE, 4);

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "PASS";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 3600000);

// Time variables
unsigned long epochNTP;
String formattedTime;
int currentHour;
int currentMinute;
int currentSecond;

String displayHours, displayMinutes;
String displayTime;
String displaySpacer;

// Function to convert epoch time to datetime
void epochToDateTime(uint32_t epoch, datetime_t* dt) {
  dt->sec = epoch % 60;
  epoch /= 60;
  dt->min = epoch % 60;
  epoch /= 60;
  dt->hour = epoch % 24;
  epoch /= 24;
  
  uint16_t days = epoch;
  uint16_t year = 1970;

  while (1) {
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    uint16_t daysInYear = leap ? 366 : 365;
    if (days < daysInYear) break;
    days -= daysInYear;
    year++;
  }

  dt->year = year;
  const uint8_t daysInMonth[] = {31, (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  dt->month = 0;
  for (int i = 0; i < 12; i++) {
    if (days < daysInMonth[i]) {
      dt->month = i + 1;
      dt->day = days + 1;
      break;
    }
    days -= daysInMonth[i];
  }
}

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

void syncRTCWithNTP() {
  // Update the NTP client and get the current epoch time
  timeClient.update();
  uint32_t epochTime = timeClient.getEpochTime();

  // Convert epoch time to datetime
  datetime_t t;
  epochToDateTime(epochTime, &t);

  // Set the RTC to the datetime
  rtc_set_datetime(&t);

  Serial.println("RTC synced with NTP");
}

void loop() {

  // Get the epoch time
  datetime_t t;

  // Get the current time from the RTC
  rtc_get_datetime(&t);

  // Print the current time
  Serial.printf("Current time: %04d-%02d-%02d %02d:%02d:%02d\n", t.year, t.month, t.day, t.hour, t.min, t.sec);


  if (t.hour > 12){
    currentHour = t.hour - 12; 
  }
  
  displayHours = String(currentHour);
  displayMinutes = String(t.min);
  displaySpacer = String("0");
  if (t.min < 10){
    displayTime = displayHours += displaySpacer += displayMinutes;
  } else{
    displayTime = displayHours += displayMinutes;
  }

  display.set(displayTime, ALIGN_RIGHT);
  display.changeDot(1);
  display.show(1000);

  static unsigned long lastSyncTime = 0;
  if (millis() - lastSyncTime > 1800000) { // 30 minutes in milliseconds
    syncRTCWithNTP();
    lastSyncTime = millis();
  }
}
