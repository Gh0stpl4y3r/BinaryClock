#ifndef MODEBUTTONDETECTION_H
#define MODEBUTTONDETECTION_H

#include "defines.h"
#include <RTClib.h>
#include <ezButton.h>


void registerButtonPress(RTC_DS1307 Rtc, ezButton buttonMode, bool *EditMode);

#endif