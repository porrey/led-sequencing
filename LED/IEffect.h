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
    //
    //
    virtual bool onAnimate();
    
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
