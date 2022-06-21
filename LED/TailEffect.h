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
// This animation will turn one LED on at a time using
// the color specified with a tail behind the lead LED.
//
class TailEffect : public IEffect
{
  public:
    //
    // Initializes the effect:
    //  leds:           The array of LEDs.
    //  numberOfLeds:   Specifies the number of LEDs.
    //  frameLength:    Specifies the length of time, in ms, to display a single frame.
    //  color:          Specifies the color of the single LED.
    //  tailLength:     Specifies the length of the tail behind the leading LED.
    //  fadeFactor:     Specifices a multiplier used to fade each subsequent LED in the tail.
    //
    TailEffect(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength, CRGB color, uint64_t tailLength, double fadeFactor) : IEffect(leds, numberOfLeds, frameLength)
    {
      this->_color = color;
      this->_tailLength = tailLength;
      this->_fadeFactor = fadeFactor;
    }

  protected:
    bool onAnimate()
    {
      //
      // Calculate the previous start and the end index
      //
      int64_t previousStart = this->_index - 1;
      int64_t previousEnd = previousStart - this->_tailLength;

      //
      // Clear the previous frame.
      //
      for (int64_t i = previousStart; i >= previousEnd; i--)
      {
        //
        // Reset the LED color.
        //
        this->setLed(i, CRGB::Black);
      }

      //
      // Calculate the current end index
      //
      int64_t currentEnd = this->_index - this->_tailLength;

      //
      // Draw the current frame.
      //
      CHSL hsl = CHSL::fromRgb(this->_color);

      for (int64_t i = this->_index; i >= currentEnd; i--)
      {
        //
        // Set the LED color.
        //
        this->setLed(i, hsl.toRgb());

        //
        // Fade each subsequent LED in the tail.
        //
        hsl.l *= this->_fadeFactor;
      }

      //
      // Increment the index.
      //
      this->_index = ++this->_index % (this->_numberOfLeds + this->_tailLength + 1);

      //
      // Return true since the animation was changed.
      //
      return true;
    }

  private:
    uint64_t _tailLength = 0;
    double _fadeFactor = 0.0;
    CRGB _color = CRGB::White;
};
