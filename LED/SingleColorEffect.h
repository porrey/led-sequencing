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
class SingleColorEffect : public IEffect
{
  public:
    //
    // Initializes the single color effect with a default frame length of 100 ms.
    //
    SingleColorEffect(CRGB *leds, uint32_t numberOfLeds, CRGB color) : IEffect(leds, numberOfLeds, 100)
    {
      this->_color = color;
    }

    //
    // Initializes the single color effect with a specified frame length.
    //
    SingleColorEffect(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength, CRGB color) : IEffect(leds, numberOfLeds, frameLength)
    {
      this->_color = color;
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
      // Set the previous LED to black (off).
      //
      this->_leds[(this->_index - 1) % this->_numberOfLeds] = CRGB::Black;

      //
      // Set the current LED to the specified color.
      //
      this->_leds[this->_index] = this->_color;

      //
      // Increment the index.
      //
      this->_index = ++this->_index % this->_numberOfLeds;

      //
      // Return true since the animation was changed.
      //
      return true;
    }

  private:
    CRGB _color = CRGB::White;
    unsigned int _index = 0;
};
