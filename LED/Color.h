#ifndef COLOR_H
#define COLOR_H

#include <FastLED.h>

class Math
{
    public:
        static double Max(double a, double b);
        static double Min(double a, double b);
        static double Modulo(double a, double b);
        static double Abs(double a);
};

typedef struct
{
    unsigned short h;
    float s;
    float l;
} CHSL;

class Color
{
  public:
    static CRGB hslToRgb(unsigned int h, double s, double l);
    static CRGB hslToRgb(CHSL hsl);
    
    static CHSL rgbToHsl(byte r, byte g, byte b);
    static CHSL rgbToHsl(CRGB rgb);
        
    static CHSL incrementHue(CHSL hsl);
    static CRGB rgbSpectrum(unsigned int index);
};

#endif
