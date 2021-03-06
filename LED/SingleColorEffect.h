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
// This animation effect will turn one LED on at a time using
// the color specified during object creation.
//
class SingleColorEffect : public IEffect
{
  public:
    //
    // Initializes the effect:
    //  leds:           The array of LEDs.
    //  numberOfLeds:   Specifies the number of LEDs.
    //  frameLength:    Specifies the length of time, in ms, to display a single frame.
    //  color:          Specifies the color of the single LED.
    //
    SingleColorEffect(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength, CRGB color) : IEffect(leds, numberOfLeds, frameLength)
    {
      this->_color = color;
    }

  protected:
    bool onAnimate()
    {
      //
      // Set the previous LED to black (off).
      //
      int64_t previousIndex = (this->_index - 1) % this->_numberOfLeds;
      this->setLed(previousIndex, CRGB::Black);

      //
      // Set the current LED to the specified color.
      //
      this->setLed(this->_index, this->_color);

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
    CRGB _color = CRGB::White;
};
