#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>
#include <HardwareSerial.h>

#define int8 int8_t

#define LEDPinTime PIN5 //Pin Output for Time
#define LEDPinDate PIN4 //Pin Output for Date
#define LEDCountTime 10 //Numer of LEDs in the "strip" for the Time
#define LEDCountDate 9 //Numer of LEDs in the "strip" for the Date

RTC_DS1307 Rtc;

//refer to this https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
Adafruit_NeoPixel LEDTimeStrip(LEDCountTime, LEDPinTime);
Adafruit_NeoPixel LEDDateStrip(LEDCountDate, LEDPinDate);

int8 OldMinute;
int8 OldDay;

void setup() {
  Serial.begin(9600);

  if (!Rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1); 
  }
  if (!Rtc.isrunning()) 
  {
    Serial.println("RTC is not running!");
    Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
    else
  {
    Serial.println("RTC is already running!");
  }
  
  LEDTimeStrip.begin();
  LEDTimeStrip.show();

  LEDDateStrip.begin();
  LEDDateStrip.show();


}

void loop() {

  DateTime CurrentDateTime = Rtc.now();
  int8 CurrentMinute = CurrentDateTime.minute();
  //If Minute hasnt Changed; Accuracy of time; only refresh rate
  if (OldMinute == CurrentMinute)
  {
    OldMinute = CurrentMinute;
    delay(1000);
    return;
  }
  int8 Hour = CurrentDateTime.hour();
  if (Hour > 12) Hour -= 12;

  DisplayBinary(CurrentMinute, 0, 6, LEDTimeStrip);
  DisplayBinary(Hour, 6, 4, LEDTimeStrip);




  //if new day: if new hour == 0 then check date
  delay(1000); 
}

void DisplayBinary (int Number, int Offset, int LedCount, Adafruit_NeoPixel &p_Strip)
{
  for (int i = 0; i < LedCount; i++)
  {
    int BitVal = (Number >> (LedCount - 1 - i)) & 1;

    if (BitVal == 1)
    {
      p_Strip.setPixelColor(Offset + i, p_Strip.Color(0, 0, 255));
    } 
    else
    {
            p_Strip.setPixelColor(Offset + i, p_Strip.Color(0, 0, 0));
    }
  }
  p_Strip.show();
}


/*

#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <RTClib.h>

#define PIN 4          // Pin connected to NeoPixels
#define NUMPIXELS 19   // Number of NeoPixel LEDs in the strip

RTC_DS1307 rtc;            // Initialize RTC object
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is not running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Initialize NeoPixel strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  DateTime now = rtc.now();  // Get current time from RTC

  int hour = now.hour();     // Get hour (0-23)
  if (hour > 12) hour -= 12; // Convert to 12-hour format
  int minute = now.minute(); // Get minute (0-59)
  int day = now.day();       // Get day (1-31)
  int month = now.month();   // Get month (1-12)

  // Display time and date in binary on NeoPixels
  displayBinary(hour, 0, 6);        // First 6 LEDs for hours
  displayBinary(minute, 6, 6);      // Next 6 LEDs for minutes
  displayBinary(day, 12, 5);        // Next 5 LEDs for day
  displayBinary(month, 17, 4);      // Last 4 LEDs for month

  delay(1000);  // Update every second
}

void displayBinary(int value, int startIndex, int numBits) {
  for (int i = 0; i < numBits; i++) {
    int bit = (value >> (numBits - 1 - i)) & 1;  // Get the bit (0 or 1)
    
    if (bit == 1) {
      strip.setPixelColor(startIndex + i, strip.Color(0, 255, 0)); // Green LED for '1'
    } else {
      strip.setPixelColor(startIndex + i, strip.Color(0, 0, 0)); // Off for '0'
    }
  }
  strip.show();  // Update the strip
}


*/