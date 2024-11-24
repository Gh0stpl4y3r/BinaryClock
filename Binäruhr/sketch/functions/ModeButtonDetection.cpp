#include <ModeButtonDetection.h>

#define LONGBUTTONPRESS 3


static DateTime startPressed;
static DateTime released;

int8 registerButtonPress(RTC_DS1307 Rtc, ezButton buttonMode)
{
    static bool isHolding = false;


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
            IsEditMode = !IsEditMode;
        }
        
    }
    if (buttonMode.isReleased())
    {
        isHolding = false;
    }
    
}