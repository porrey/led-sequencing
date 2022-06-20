/*
 * The MIT License (MIT)
 * 
 * Copyright © 2022 Daniel Porrey
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the “Software”), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial 
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 #include "CHSL.h"

CRGB CHSL::toRgb()
{
  return CHSL::toRgb(this->h, this->s, this->l);
}

CRGB CHSL::toRgb(uint16_t h, double s, double l)
{
  double hd = (double)(h % 360);

  double chroma = (1 - Math::Abs((2.0 * l) - 1.0)) * s;
  double h1 = hd / 60.0;
  double x = chroma * (1.0 - Math::Abs(Math::Modulo(h1, 2.0) - 1.0));
  double m = l - (0.5 * chroma);
  double r1, g1, b1;

  if (h1 < 1.0)
  {
    r1 = chroma;
    g1 = x;
    b1 = 0;
  }
  else if (h1 < 2.0)
  {
    r1 = x;
    g1 = chroma;
    b1 = 0;
  }
  else if (h1 < 3.0)
  {
    r1 = 0;
    g1 = chroma;
    b1 = x;
  }
  else if (h1 < 4.0)
  {
    r1 = 0;
    g1 = x;
    b1 = chroma;
  }
  else if (h1 < 5.0)
  {
    r1 = x;
    g1 = 0;
    b1 = chroma;
  }
  else
  {
    r1 = chroma;
    g1 = 0;
    b1 = x;
  }

  byte r = (byte)(255 * (r1 + m));
  byte g = (byte)(255 * (g1 + m));
  byte b = (byte)(255 * (b1 + m));

  return CRGB(r, g, b);
}

CRGB CHSL::toRgb(CHSL hsl)
{
  return CHSL::toRgb(hsl.h, hsl.s, hsl.l);
}

CHSL CHSL::fromRgb(byte r, byte g, byte b)
{
  const double toDouble = 1.0 / 255.0;
  double r1 = toDouble * r;
  double g1 = toDouble * g;
  double b1 = toDouble * b;
  double max = Math::Max(Math::Max(r1, g1), b1);
  double min = Math::Min(Math::Min(r1, g1), b1);
  double chroma = max - min;
  double h1;

  if (chroma == 0)
  {
    h1 = 0;
  }
  else if (max == r1)
  {
    // The % operator doesn't do proper modulo on negative
    // numbers, so we'll add 6 before using it
    h1 = Math::Modulo((((g1 - b1) / chroma) + 6), 6);
  }
  else if (max == g1)
  {
    h1 = 2.0 + ((b1 - r1) / chroma);
  }
  else
  {
    h1 = 4.0 + ((r1 - g1) / chroma);
  }

  double lightness = 0.5 * (max + min);
  double saturation = chroma == 0 ? 0 : chroma / (1.0 - Math::Abs((2.0 * lightness) - 1.0));

  return { round(60.0 * h1), saturation, lightness };
}

CHSL CHSL::fromRgb(CRGB rgb)
{
  return CHSL::fromRgb(rgb.r, rgb.g, rgb.b);
}

void CHSL::incrementHue()
{
  this->h = ++this->h % 360;
}

CHSL CHSL::incrementHue(CHSL hsl)
{
  hsl.h = ++hsl.h % 360;
  return hsl;
}

CRGB CHSL::rgbSpectrum(uint32_t index)
{
  CRGB returnValue = CRGB(0, 0, 0);

  if (index >= 0 && index < 256)
  {
    returnValue.r = 255;
    returnValue.g = (byte)index;
    returnValue.b = 0;
  }
  else if (index >= 256 && index < 510)
  {
    returnValue.r = (byte)(255 - (index % 255));
    returnValue.g = 255;
    returnValue.b = 0;
  }
  else if (index >= 510 && index < 765)
  {
    returnValue.r = 0;
    returnValue.g = 255;
    returnValue.b = (byte)(index % 255);
  }
  else if (index >= 765 && index < 1020)
  {
    returnValue.r = 0;
    returnValue.g = (byte)(255 - (index % 255));
    returnValue.b = 255;
  }
  else if (index >= 1020 && index < 1275)
  {
    returnValue.r = (byte)(index % 255);
    returnValue.g = 0;
    returnValue.b = 255;
  }
  else if (index >= 1275 && index < 1530)
  {
    returnValue.r = 255;
    returnValue.g = 0;
    returnValue.b = (byte)(255 - (index % 255));
  }
  else if (index == 1530)
  {
    returnValue.r = 255;
    returnValue.g = 0;
    returnValue.b = 0;
  }

  return returnValue;
}
