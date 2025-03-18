#ifndef EDITMODE_H
#define EDITMODE_H

#include <RTClib.h>
#include <ezButton.h>
#include <enums.h>

void handleEditMode(RTC_DS1307 &Rtc, ezButton &buttonMode, ezButton &buttonInc, ezButton &buttonDec, bool *p_EditMode, EditState &state);

#endif