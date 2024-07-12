/*
ShiftDisplay2 example
by Ameer Dawood
Count minutes passing by
https://ameer.io/ShiftDisplay2/
*/

#include <ShiftDisplay2.h>

// Arduino pin 6 connected to shift register latch, pin 7 to clock and pin 5 to data
// common anode display with 2 digits
ShiftDisplay2 display(9, 10, 11, COMMON_CATHODE, 4);

void loop() {
	// for 4 seconds, show temperature with one decimal, aligned to center of display
	display.set("1234");
	display.show(4000);

	// show condition with marquee effect
	while (condition.length() > 0) {
		display.set("5678");
		display.show(500);
		condition.remove(0,1);
	}
}
