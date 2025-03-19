#include "defines.h"
#include "displayBinary.h"

void DisplayBinary(int Number, int Offset, int LedCount, Adafruit_NeoPixel &p_Strip)
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