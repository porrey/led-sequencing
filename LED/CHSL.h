/*
   The MIT License (MIT)

   Copyright © 2022 Daniel Porrey

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software
   and associated documentation files (the “Software”), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial
   portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
   LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CHSL_H
#define CHSL_H

#include "Math.h"
#include <FastLED.h>

class CHSL
{
  public:
    CHSL();
    CHSL(uint16_t);
    CHSL(uint16_t, double, double);
    uint16_t h = 0;
    double s = 1.0;
    double l = 0.5;

    CRGB toRgb();
    void incrementHue();

    static CHSL fromRgb(byte, byte, byte);
    static CHSL fromRgb(CRGB);
    static CHSL incrementHue(CHSL);

    static CRGB toRgb(uint16_t, double, double);
    static CRGB toRgb(CHSL);
    static CRGB rgbSpectrum(uint32_t);
};

#endif
