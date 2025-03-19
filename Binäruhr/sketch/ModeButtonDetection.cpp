#include "ModeButtonDetection.h"

#define LONGBUTTONPRESS 3

static bool isHolding = false;

static DateTime startPressed;
static DateTime released;

void registerButtonPress(RTC_DS1307 Rtc, ezButton buttonMode, bool *IsEditMode)
{

    if (buttonMode.isPressed() && !isHolding)
    {
        startPressed = Rtc.now();
        isHolding = true;
    }
    else if (isHolding)
    {
        released = Rtc.now();
        TimeSpan buttonPressedFor = released - startPressed;

        if (buttonPressedFor.totalseconds() >= LONGBUTTONPRESS)
        {
            *IsEditMode = !IsEditMode;
        }
    }
    if (buttonMode.isReleased())
    {
        isHolding = false;
    }
}