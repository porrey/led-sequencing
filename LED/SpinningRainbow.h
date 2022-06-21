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
#include "IEffect.h"

//
// This animation effect will cycle the entire strip
// through the spectrum of colors.
//
class SpinningRainbow : public IEffect
{
  public:
    //
    // Initializes the effect:
    //  leds:           The array of LEDs.
    //  numberOfLeds:   Specifies the number of LEDs.
    //  frameLength:    Specifies the length of time, in ms, to display a single frame.
    //
    SpinningRainbow(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength) : IEffect(leds, numberOfLeds, frameLength)
    {
    }

    //
    // Resets this animation effect by setting the
    // starting LED back to 0 and then calls the base
    // implementation.
    //
    bool reset()
    {
      Serial.println("HueWheelEffect::reset()");

      //
      // Divide the hue (360) by the number of LEDs to
      // to evenly distribute the hue range across each LED.
      //
      this->_offsetBase = (uint32_t)(360.0 / (float)this->_numberOfLeds);
      Serial.print("Offset Base = "); Serial.println(this->_offsetBase);

      //
      // Call the base reset.
      //
      return IEffect::reset();
    }

  protected:
    bool onAnimate()
    {
      for (uint64_t i = 0; i < this->_numberOfLeds; i++)
      {
        //
        // Calulate the hue for the current LED.
        //
        uint32_t hue = (this->_offsetBase * i);

        //
        // Create the HSL color with the given hue.
        //
        CHSL hsl = CHSL(hue);

        //
        // Set the LED color.
        //
        this->setLed((i + this->_index) % this->_numberOfLeds, hsl.toRgb());
      }

      //
      // Increment the index.
      //
      this->increment();

      //
      // Return true since the animation was changed.
      //
      return true;
    }

  private:
    uint32_t _offsetBase = 0;
};
