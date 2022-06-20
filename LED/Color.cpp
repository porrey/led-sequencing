#include "Color.h"

CRGB Color::hslToRgb(unsigned int h, double s, double l)
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

CRGB Color::hslToRgb(CHSL hsl)
{
  return Color::hslToRgb(hsl.h, hsl.s, hsl.l);
}

CHSL Color::rgbToHsl(byte r, byte g, byte b)
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

CHSL Color::rgbToHsl(CRGB rgb)
{
  return Color::rgbToHsl(rgb.r, rgb.g, rgb.b);
}

CHSL Color::incrementHue(CHSL hsl)
{
  hsl.h = ++hsl.h % 360;
  return hsl;
}

CRGB Color::rgbSpectrum(unsigned int index)
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

//
// Math
//
double Math::Max(double a, double b)
{
  double returnValue = a;

  if (a > b)
  {
    returnValue = a;
  }
  else
  {
    returnValue = b;
  }

  return returnValue;
}

double Math::Min(double a, double b)
{
  double returnValue = a;

  if (a < b)
  {
    returnValue = a;
  }
  else
  {
    returnValue = b;
  }

  return returnValue;
}

double Math::Modulo(double a, double b)
{
  return a - (b * ((int)(a / b)));
}

double Math::Abs(double a)
{
  double returnValue = a;

  if (a < 0)
  {
    returnValue = a * -1;
  }

  return returnValue;
}
