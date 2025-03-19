#include "defines.h"
#include <RTClib.h>
#include "enums.h"
#include "displayBinary.h"
#include "EditMode.h"

// refer to this https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
Adafruit_NeoPixel LEDTimeStrip(LEDCountTime, LEDPinTime);
Adafruit_NeoPixel LEDDateStrip(LEDCountDate, LEDPinDate);

RTC_DS1307 Rtc;

int8 OldDay;
int8 OldMinute;

bool *p_EditMode = new bool(false);
EditState State = MINUTE;

ezButton buttonMode(BUTTON_MODE_PIN, true);
ezButton buttonDec(BUTTON_DEC_PIN, true);
ezButton buttonInc(BUTTON_INC_PIN, true);

void setup()
{

  Serial.begin(9600);

  if (!Rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
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

  buttonMode.setDebounceTime(50);
  buttonDec.setDebounceTime(50);
  buttonInc.setDebounceTime(50);
}

void loop()
{

  handleEditMode(Rtc, buttonMode, buttonInc, buttonDec, p_EditMode, State);

  DateTime CurrentDateTime = Rtc.now();
  int8 CurrentMinute = CurrentDateTime.minute();

  // If Minute hasnt Changed; Accuracy of time; its only refresh rate
  if (OldMinute == CurrentMinute)
  {
    OldMinute = CurrentMinute;
    delay(1000);
    return;
  }
  int8 Hour = CurrentDateTime.hour();
  if (Hour > 12)
  {
    Hour -= 12;
  }
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
