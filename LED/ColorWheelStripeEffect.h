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
// This animation effect will create a stripe of specified length
// the moves from end of the strip to the other while cycling
// through colors.
//
class ColorWheelStripeEffect : public IEffect
{
  public:
    //
    // Initializes the effect:
    //  leds:           The array of LEDs.
    //  numberOfLeds:   Specifies the number of LEDs.
    //  frameLength:    Specifies the length of time, in ms, to display a single frame.
    //  length:         Specifies the length of the stripe (number of lLEds lit up).
    //
    ColorWheelStripeEffect(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength, uint64_t length) : IEffect(leds, numberOfLeds, frameLength)
    {
      this->_length = length;
    }

    //
    // Resets this animation effect by setting the
    // starting LED back to 0 and then calls the base
    // implementation.
    //
    bool reset()
    {
      //
      // Reset the _currentStart, _currentEnd and _frame.
      //
      this->_currentStart = 0;
      this->_currentEnd = this->_currentStart - this->_length + 1;
      this->_frame = 0;

      //
      // Call the base reset.
      //
      return IEffect::reset();
    }

  protected:
    bool onAnimate()
    {
      //
      // This animation will change the color of the stripe 5
      // times before moving it.
      //
      if (this->_frame % 5 == 0)
      {
        //
        // Clear the first and last LED of the previous frame.
        //
        this->setLed(this->_currentStart, CRGB::Black);
        this->setLed(this->_currentEnd, CRGB::Black);

        //
        // Move the stripe forward.
        //
        this->_currentStart = (this->_currentStart + 1) % (this->_numberOfLeds + this->_length - 1);
        this->_currentEnd = this->_currentStart - this->_length + 1;
      }

      //
      // Update the color using the RGB spectrum. There are 1,530
      // colors in the spectrum.
      //
      for (int64_t i = this->_currentStart; i >= this->_currentEnd; i--)
      {
        this->setLed(i, CHSL::rgbSpectrum(this->_frame));
      }

      //
      // Increment the frame counter. Limit the frame counter
      // in the range of 0 to 1529.
      //
      this->_frame = (this->_frame + 1) % 1530;

      //
      // Return true since the animation was changed.
      //
      return true;
    }

  private:
    uint16_t _frame = 0;
    uint64_t _length = 1;
    int64_t _currentStart = 0;
    int64_t _currentEnd = 0;
};
