# Arcade-WiFiClock
## Alternative firmware for the Hack Club Hack Hour Clock (Arcade Ticket Counter) that displays the current time using NTP.

### Patch Notes - V1

* Fixed Display flashing issues
* Relelaxed NTP syncs from 100ms to 1s
* Overflow protection (prevents negative or unregular hours and times with more than 60 minutes)
* Allows GMT offsets with half hours (EX: IST = GMT+5:30)
* Adjusted calculations for more time zones
* Option to easily disable/enable 12 Hour cycles


## Installation:

* Install Ardunio IDE 2.0 or newer
* Add the Pi Pico W(H) in Additional Board Manager URLs:

```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

```

* Install the following Ardunio Libaries 
  - ShiftDisplay2: manages the display
  - NTPCilent: allows for communication with NTP servers

* Download the V1.ino file from the repo.
* You can also use the RTCexperimental.ino as another option for a less internet-dependent option but is nowhere near finished

* Open it in Ardunio IDE

* Plug in the clock and select "Raspberry Pi Pico W" in the proper serial port
       - If installing this for the first time especially after other firmware, hold BOOTSEL on the rear of the clock before plugging in

* Edit the SSID and PASS near the top to match your WiFi

* Set the GMT offset on Line 59 by adjusting the "-4" (EST) to yours

* Select Verify, wait for the compilation to complete 

* Select Upload, wait for the Pi to finish flashing

## Start up sequence

* The clock will appear blank for at least 10 seconds
       - This is normal, the clock is attempting to connect to your WiFi and establish NTP, this may take up to a minute.

* Then, the clock will display "SYnC"
        - The clock has established a connection and calculating the correct time

* Then, the clock should display the time

* If the clock starts flashing slowly, the clock has lost contact with NTP. Either restart the clock or fixing WiFi issues to fix this.




