#include <Adafruit_NeoPixel.h>
#include <RTClib.h>
#include <Wire.h>
#include <Arduino.h>

#define int8 int8_t

#define LEDPinTime PIN5 //Pin Output for Time
#define LEDPinDate PIN4 //Pin Output for Date
#define LEDCountTime 10 //Numer of LEDs in the "strip" for the Time
#define LEDCountDate 9 //Numer of LEDs in the "strip" for the Date

RTC_DS1307 Rtc;

//refer to this https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
Adafruit_NeoPixel LEDTimeStrip(LEDCountTime, LEDPinTime);
Adafruit_NeoPixel LEDDateStrip(LEDCountDate, LEDPinDate);

int8 OldDay;
int8 OldMinute;
  

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

  //If Minute hasnt Changed; Accuracy of time; its only refresh rate
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
  OldMinute = CurrentMinute;

  int currentday = CurrentDateTime.day();
  if (currentday != OldDay)
  {
    OldDay = currentday;
    int currentMonth = CurrentDateTime.month();
    DisplayBinary(currentMonth, 0, 4, LEDDateStrip);
    DisplayBinary(currentday, 4, 5, LEDDateStrip);
    delay(1000); 
  }
}

void DisplayBinary (int Number, int Offset, int LedCount, Adafruit_NeoPixel &p_Strip)
{
  for (int i = 0; i < LedCount; i++)
  {
    int BitVal = (Number >> i) & 1;

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