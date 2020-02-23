#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "Wire.h"

//// DEFINES //////////////////////////////////////////////////////////////////
// Arduino Pins for GPS
#define txGPSPin 6
#define rxGPSPin 5
#define gpsBaud  9600

// Arduino Pins for OLED Screen
#define sclk 13     // scl
#define mosi 11     // sda
#define cs   10     // cd
#define dc   9      // rst
#define rst  8      // dc

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
  printInColor("Zhenia's Arduino", RED);
  delay(1000);
}
// Displays basic information from the GPS unit
void displayBasicInfo() {
  display.fillScreen(BLACK);
  display.setCursor(0, 0);
  printInColor("GPS\n", GREEN);
  printInColor("Lat: ", CYAN);
  display.println(gps.location.lat());
  printInColor("Lon: ", CYAN);
  display.println(gps.location.lng());
  printInColor("Sats: ", CYAN);
  display.println(gps.satellites.value());
  printInColor("Alt: ", CYAN);
  display.println(gps.altitude.feet());
}
// Displays time and date from the GPS unit
void displayTimeAndDate() {
  display.fillScreen(BLACK);
  display.setCursor(0, 0);
  printInColor("Current Time: \n", GREEN);

  display.print(gps.time.hour() + 4);
  display.print(":");
  display.print(gps.time.minute());
  display.print(":");
  display.print(gps.time.second());
}
// Prints a line in a specified Color
void printInColor(String text, uint16_t color) {
  display.setTextColor(color);
  display.print(text);
  display.setTextColor(OledTextColor);
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
  if(gps.location.isUpdated()) {
    displayBasicInfo();
    delay(1500);
    displayTimeAndDate();
    delay(1500);
  }
}