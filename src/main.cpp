#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET);

void setup() {
#ifdef __AVR_ATmega328P__
    Wire.begin();
#else
    Wire.begin(D4, D5);
#endif

    Serial.begin(9600);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;  // Don't proceed, loop forever
    }
    display.display();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
}

void loop() {
    WiFi.scanNetworks();
    int numNetworks = WiFi.scanComplete();
    display.clearDisplay();
    display.setCursor(0,0);
    for (int i = 0; i < numNetworks; i++) {
        display.println(WiFi.SSID(i));
    }
    display.display();
    delay(1000);
}