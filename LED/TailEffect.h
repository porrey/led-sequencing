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
#include "IEffect.h"

//
// This animation will turn one LED on at a time using
// the color specified during object creation.
//
class TailEffect : public IEffect
{
  public:
    //
    // Initializes the tail effect with a specified frame length and tail length.
    //
    TailEffect(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength, CRGB color, uint32_t tailLength) : IEffect(leds, numberOfLeds, frameLength)
    {
      this->_color = color;
      this->_tailLength = tailLength;
    }

    //
    // Resets this animation effect by setting the
    // starting LED back to 0 and then calls the base
    // implementation.
    //
    bool reset()
    {
      //
      // Reset the current LED index to 0.
      //
      this->_index = 0;

      //
      // Call the base reset.
      //
      return IEffect::reset();
    }

  protected:
    //
    // This animation turns on one LED at a time and turns
    // off the previous LED. To be efficient, it does not
    // change any other LEDs. Reset should be called on
    // this animation before it is started.
    //
    bool onAnimate()
    {
      //
      // Calculate the previous start and the end index
      //
      uint32_t previousStart = this->_index - 1;
      int32_t previousEnd = previousStart - this->_tailLength;

      //
      // Clear the previous frame.
      //
      for (int i = previousStart; i >= previousEnd; i--)
      {
        if (i >= 0 && i < this->_numberOfLeds)
        {
          this->_leds[i] = CRGB::Black;
        }
      }

      //
      // Calculate the current end index
      //
      int32_t currentEnd = this->_index - this->_tailLength;

      //
      // Draw the current frame.
      //
      CHSL hsl = CHSL::fromRgb(this->_color);

      for (int i = this->_index; i >= currentEnd; i--)
      {
        if (i >= 0 && i < this->_numberOfLeds)
        {
          //
          // Set the color.
          //
          this->_leds[i] = hsl.toRgb();

          //
          // Fade each subsequent LED in the tail.
          //
          hsl.l *= .85;
        }
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
    uint32_t _tailLength = 0;
    CRGB _color = CRGB::White;
    unsigned int _index = 0;
};
