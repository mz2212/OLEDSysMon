#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

char mode, d1, d2;
char buff[16] = "";

void setup() {
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);

	Serial.begin(9600);
}

void loop() {
	if(Serial.available() > 0) {
		// So I guess I figured a better way of handling this.
		// A multi-byte protocol is how I'm going to handle it now.
		// I.E. 'C''10''24' to set the clock/timer string.
		// I might add a cursor positioning thingy later.
		mode = Serial.read();
		if(mode == 'A') { // Blank the display.
			display.setCursor(0, 0);
			display.clearDisplay();
			display.display();
		}
		if(mode == 'B') { // Prepare for writing.
			display.setCursor(0, 0);
			display.clearDisplay();
		}
		if(mode == 'C') { // Set time string
			display.setCursor(0, 0);
			while(Serial.available() == 0) {}
			d1 = Serial.read();
			while(Serial.available() == 0) {}
			d2 = Serial.read();
			sprintf(buff, "%02d:%02d", d1, d2);
			display.print(buff);
		}
		if(mode == 'D') { // Set CPU String
			display.setCursor(0, 16); // Characters are 16px tall/8px wide.
			while(Serial.available() == 0) {}
			d1 = Serial.read();
			sprintf(buff, "CPU:%d%%", d1);
			display.print(buff);
		}
		if(mode == 'Z') {
			display.display();
		}
	}
}
