#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

int data = 0;
char buff[4] = "";
String toPrint = "";

void setup() {
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setTextSize(2);

	Serial.begin(9600);
}

void loop() {
	if(Serial.available() > 0) {
		// This is really clumsy, but it's the best I can figure...
		// The limits are basically what fit in a byte,
		// though with a bit of cleverness, you can get around that.
		//Time/Countdown... Somthing like that.
		display.setCursor(0, 0);
		display.clearDisplay();
		data = Serial.read();
		sprintf(buff, "%02d", data);
		display.print(buff); display.print(":");
		while(Serial.available() == 0) {}
		data = Serial.read();
		sprintf(buff, "%02d", data);
		display.println(buff);
		//CPU Usage
		while(Serial.available() == 0) {}
		data = Serial.read();
		display.print("CPU:");
		display.print(data);
		display.println("%");
		
		display.display();
	}
}
