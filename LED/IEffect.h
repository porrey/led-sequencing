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
#ifndef I_EFFECT_H
#define I_EFFECT_H

#include <FastLED.h>

//
// Defines the interface for an LED animation effect.
//
class IEffect
{
  public:
    IEffect(CRGB*, uint32_t);
    IEffect(CRGB*, uint32_t, uint64_t);
    ~IEffect();

    //
    // Defines the number of milliseconds to display a given frame. One frame
    // is the state of the entire strip (or set of LEDs) that make of the
    // whole of the effect. Typically the effect is over the entire strip in
    // which case the enitre strip is set in one call to animate(). The default
    // value is 0 which disables animation.
    //
    uint64_t frameLength = 0;

    //
    // Returns true if the current frame has exceeded its time
    // length and is ready to be moved to the next animation frame.
    //
    virtual bool readyToAnimate();

    //
    // Animates the effect. This method can be called as often as
    // possible. It cannot be called too often but if not called
    // often enough the effect may not animate properly.
    //
    virtual bool animate();

    //
    // Resets the effect to start at the beginning. The deafult
    // implementation will clear the strip, but an effect can
    // override this behavior.
    //
    virtual bool reset();

  protected:
    //
    // Peforms the work of a single frame of animation.
    //
    virtual bool onAnimate();

    //
    // Increment _index keeping it within the
    // bounds of the LED array.
    //
    virtual void increment();

    //
    // Sets the color of an LED ensuring the index specified
    // is within the range of LEDs. This is useful when the
    // effect may use values below 0 or above the LED length
    // so the dframe can be drawn "offscreen".
    //
    virtual void setLed(int64_t index, CRGB rgb);

    //
    // The current LED.
    //
    int64_t _index = 0;

    //
    // The number of LEDs.
    //
    uint64_t _numberOfLeds = 0;

    //
    // Marks the last time the sequence/animation was advanced.
    //
    uint64_t _lastAnimationTime = 0;

    //
    // Array of LEDs.
    //
    CRGB* _leds;
};
#endif
