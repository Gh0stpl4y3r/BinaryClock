#include "EditMode.h"

void handleEditMode(RTC_DS1307 &Rtc, ezButton &buttonMode, ezButton &buttonInc, ezButton &buttonDec, bool *p_EditMode, EditState &state) {
    static unsigned long modePressTime = 0;
    static DateTime currentTime;
    static int editValues[4];
    
    buttonMode.loop();
    buttonInc.loop();
    buttonDec.loop();
    
    if (buttonMode.isPressed()) {
        modePressTime = millis();
    }
    
    if (buttonMode.isReleased()) {
        if (millis() - modePressTime > 2000) {
            *p_EditMode = !(*p_EditMode);
            if (*p_EditMode) {
                currentTime = Rtc.now();
                editValues[MINUTE] = currentTime.minute();
                editValues[HOUR] = currentTime.hour();
                editValues[DAY] = currentTime.day();
                editValues[MONTH] = currentTime.month();
            } else {
                Rtc.adjust(DateTime(currentTime.year(), editValues[MONTH], editValues[DAY], editValues[HOUR], editValues[MINUTE], 0));
            }
        } else if (*p_EditMode) {
            state = static_cast<EditState>((state + 1) % 4);
        }
    }
    
    if (*p_EditMode) {
        if (buttonInc.isPressed()) editValues[state] = (editValues[state] + 1) % (state < 2 ? 60 : (state == 2 ? 32 : 13));
        if (buttonDec.isPressed()) editValues[state] = (editValues[state] - 1 + (state < 2 ? 60 : (state == 2 ? 32 : 13))) % (state < 2 ? 60 : (state == 2 ? 32 : 13));
    }
}
