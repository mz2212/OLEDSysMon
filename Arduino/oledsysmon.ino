#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

Adafruit_SSD1306 display(4);

char mode, d1, d2;
char buff[16] = "";
String cond = "";

void setup() {
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);
	//display.drawBitmap(32, 0, wifi, 64, 50, WHITE);
	//display.display(); // Test the wifi icon.
	// This stuff will be handy for when I get my esp8285 in. On an uno, not quite as much.

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
		if(mode == 'E') { // Weather
			display.setCursor(0, 32);
			display.print("WEATHER");
			display.drawFastHLine(0, 46, 128, WHITE);
			while(Serial.available() == 0) {}
			d1 = Serial.read(); // The coord system for bitmap drawing is bass ackwards
			if(d1 == 'A'){ display.drawBitmap(114, 48, sunny, 13, 13, WHITE); cond = "CLEAR"; }
			if(d1 == 'B'){ display.drawBitmap(114, 48, fewClouds, 13, 8, WHITE); cond = "OVCST"; }
			if(d1 == 'C'){ display.drawBitmap(114, 48, clouds, 13, 5, WHITE); cond = "CLDY"; }
			if(d1 == 'D'){ display.drawBitmap(114, 48, rain, 13, 10, WHITE); cond = "RAIN"; }
			if(d1 == 'E'){ display.drawBitmap(114, 48, tstorm, 13, 10, WHITE); cond = "TSTRM"; }
			if(d1 == 'F'){ display.drawBitmap(114, 48, snow, 9, 9, WHITE); cond = "SNOW"; }
			if(d1 == 'G'){ display.drawBitmap(114, 48, fog, 14, 12, WHITE); cond = "FOG"; }
			while(Serial.available() == 0) {}
			d1 = Serial.read();
			display.setCursor(0, 48);
			sprintf(buff, "%dC:", d1);
			display.print(buff);
			display.print(cond);
		}
		if(mode == 'Z') {
			display.display();
		}
	}
}
