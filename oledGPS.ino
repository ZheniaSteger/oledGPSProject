#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "Wire.h"

//// DEFINES //////////////////////////////////////////////////////////////////
// Arduino Pins for GPS
#define rxGPSPin 0
#define txGPSPin 1
#define gpsBaud  9600

// Arduino Pins for OLED Screen
#define sclk 13     // scl
#define mosi 11     // sda
#define cs   10     // cd
#define rst  9      // dc
#define dc   8      // rst

// Colors
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

// Default Colors
#define OledTextColor   MAGENTA
#define OledBackColor   BLACK

//// VARIABLES ////////////////////////////////////////////////////////////////
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst); // The display
TinyGPSPlus gps; // The GPS
SoftwareSerial gpsSerial(rxGPSPin, txGPSPin); // Software serial interface for the GPS

//// FUNCTIONS ////////////////////////////////////////////////////////////////
// Initializes the oled display
void initializeDisplay() {
  display.begin();
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.setTextColor(OledTextColor);
  display.setTextSize(1);
  display.print("Zhenia's Arduino");
  delay(1000);
}
// Displays basic information from the GPS unit
void displayBasicInfo() {
  display.fillScreen(BLACK);
  display.setCursor(0, 0);
  display.println("GPS");
  display.print("Lat: ");
  display.println(gps.location.lat());
  display.print("Lon: ");
  display.println(gps.location.lng());
  display.print("Sats: ");
  display.println(gps.satellites.value());
  display.print("Alt: ");
  display.println(gps.altitude.feet());
}
// Displays time and date from the GPS unit
void displayTimeAndDate() {
  display.fillScreen(BLACK);
  display.setCursor(0, 0);
  display.println("Current Time");
  display.println(gps.time.hour() + ":" + gps.time.minute() + ":" + gps.time.second());
}

//// SETUP ////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Serial.println("Online");

  gpsSerial.begin(gpsBaud);
  Serial.println(TinyGPSPlus::libraryVersion());

  initializeDisplay();
}
//// LOOP /////////////////////////////////////////////////////////////////////
void loop() {
  while(gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
  if(gps.location.isUpdated() {
	  displayInfo();
  }
}
