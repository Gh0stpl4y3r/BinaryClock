#ifndef MODEBUTTONDETECTION_H
#define MODEBUTTONDETECTION_H

#include <defines.h>
#include <RTClib.h>
#include <ezButton.h>

extern bool IsEditMode;
int8 registerButtonPress(RTC_DS1307 Rtc, ezButton buttonMode);

#endif