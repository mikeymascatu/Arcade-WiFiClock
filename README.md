# Arcade-WiFiClock
## Alternative firmware for the Hack Club Hack Hour Clock (Arcade Ticket Counter) that displays the current time using NTP.

## Installation:

* Install Ardunio IDE 2.0 or newer
* Add the Pi Pico W(H) in Additional Board Manager URLs:

```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

```

* Install the following Ardunio Libaries 
  - ShiftDisplay2: manages the display
  - NTPCilent: allows for communication with NTP servers

* Download the V0.1B.ino file from the repo.

* Open it in Ardunio IDE

* Plug in the clock and select "Raspberry Pi Pico W" in the proper serial port
  - If installing this for the first time especially after other firmware, hold BOOTSEL on the rear of the clock before plugging in

* Edit the SSID and Password near the top to match your WiFi

* Set the GMT offset on Line __ by adjusting the "-4" (EST) to yours

* Select Verify, wait for the compilation to complete 

* Select Upload, wait for the Pi to finish flashing

## Start up sequence

* The clock will appear blank for at least 10 seconds
 - This is normal, the clock is attempting to connect to your WiFi and establish NTP, this may take up to a minute.

* Then, the clock will display "SYnC"
- The clock has established a connection and calculating the correct time

* Then, the clock should display the time
 - The clock flashes roughly every 300ms, this normal as the clock refreshes it's NTP connection. 




