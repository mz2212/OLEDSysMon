#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#ifdef CONFIGURED
#include "conf.h"
#else
#include "confExample.h"
#endif

#include "icons.h"

void update(void *pArg);
void doWeather();
String convertCond(String i);

WiFiUDP ntpUDP;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 14, 12);
NTPClient timeClient(ntpUDP, "time.nist.gov", -25200, 60000);
DynamicJsonBuffer jsonBuffer(1024);

float temp;
String cond;
char textBuff[32];
String currTime;
String url;
ETSTimer myTimer;

void setup()
{
    Serial.begin(115200);

    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso16_tf);

    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
        u8g2.clearBuffer();
        u8g2.drawXBM(32, 14, 64, 64, wifi);
        u8g2.sendBuffer();
        delay(100);
    }
    url = "/data/2.5/weather?id="+city+"&appid="+appId+"&units="+units;
    timeClient.begin();
    os_timer_setfn(&myTimer, update, NULL);
    os_timer_arm(&myTimer, 900000, true);
    update(NULL);
}

void loop() {
    timeClient.update();
    u8g2.clearBuffer();
    currTime = timeClient.getFormattedTime();
    strcpy(textBuff, currTime.c_str());
    u8g2.drawStr(0, 16, textBuff);
    #ifdef RSSI
    sprintf(textBuff, "%d%s", WiFi.RSSI(), "dB");
    u8g2.drawStr(78, 16, textBuff); // I didn't like this much
    #endif
    sprintf(textBuff, "%.1f%s:%s", temp, "C", convertCond(cond).c_str());
    u8g2.drawStr(0, 32, textBuff);
    u8g2.sendBuffer();
    delay(250);
}

void update(void *pArg) {
    doWeather();
}

void doWeather() {
    HTTPClient http;
    http.begin("http://api.openweathermap.org"+url);
    http.GET();
    String payload = http.getString();

    JsonObject& root = jsonBuffer.parseObject(payload);
    temp = root["main"]["temp"];
    cond = convertCond(root["weather"][0]["icon"].as<char*>());

    http.end();
}

String convertCond(String i) {
    if(i == "01d" || i == "01n" || i == "CLEAR"){ u8g2.drawXBM(114, 16, 13, 13, sunny); return "CLEAR"; }
    if(i == "02d" || i == "02n" || i == "OVCST"){ u8g2.drawXBM(114, 16, 13, 8, fewClouds); return "OVCST"; }
    if(i == "03d" || i == "03n" || i == "04d" || i == "04n" || i == "CLDY"){ u8g2.drawXBM(114, 16, 13, 5, clouds); return "CLDY"; }
    if(i == "09d" || i == "09n" || i == "RAIN"){ u8g2.drawXBM(114, 16, 13, 10, rain); return "RAIN"; }
    if(i == "11d" || i == "11n" || i == "TSTRM"){ u8g2.drawXBM(114, 16, 13, 10, tstorm); return "TSTRM"; }
    if(i == "13d" || i == "13n" || i == "SNOW"){ u8g2.drawXBM(114, 16, 9, 9, snow); return "SNOW"; }
    if(i == "50d" || i == "FOG"){ u8g2.drawXBM(114, 16, 14, 12, fog); return "FOG"; }
    return "?";
}
