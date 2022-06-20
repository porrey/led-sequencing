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
// Initialize the effect with an LED array and the number of LEDs.
//
IEffect::IEffect(CRGB *leds, uint32_t numberOfLeds)
{
  this->_leds = leds;
  this->_numberOfLeds = numberOfLeds;
};

//
// Initialize the effect with an LED array, the number of LEDs,
// and the frame length.
//
IEffect::IEffect(CRGB *leds, uint32_t numberOfLeds, uint64_t frameLength)
{
  this->_leds = leds;
  this->_numberOfLeds = numberOfLeds;
  this->frameLength = frameLength;
};

//
// Deconstructor: remove thr reference to the LEDs.
//
IEffect::~IEffect()
{
  this->_leds = NULL;
};

//
// Base implementation of animate calls
// readyToAnimate() and then onAnimate().
//
bool IEffect::animate()
{
  bool returnValue = false;

  if (this->readyToAnimate())
  {
    returnValue = this->onAnimate();
  }
};

//
// The main animation code goes here...
//
bool onAnimate()
{
  return false;
}

//
// Resets the animation. The default implementation
// sets the last time to zero so the animation can restart
// immediately, clears LED strip and updates the LEDs.
//
bool IEffect::reset()
{
  Serial.println("IEffect::reset()");

  //
  // Set the last animation time to 0 so the next
  // animation starts immediately.
  //
  this->_lastAnimationTime = 0;

  //
  // Clear the strip.
  //
  FastLED.clear();
  FastLED.show();

  return true;
};

//
// The default implementation checks the last animation
// time against the frame length and returns true if the
// current frame has expired.
//
bool IEffect::readyToAnimate()
{
  bool returnValue = false;

  //
  // Only animate if frame length is greater than 0.
  //
  if (this->frameLength > 0)
  {
    //
    // animate() can be called as often as possible, but an effect
    // runs a specified rate. If animate() is not called often enough
    // the effect may run slow.
    //
    if (this->_lastAnimationTime == 0 || millis() - this->_lastAnimationTime >= this->frameLength)
    {
      //
      // Get and store the value of millis()
      //
      this->_lastAnimationTime = millis();
      returnValue = true;
    }
  }

  return returnValue;
};
