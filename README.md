# LED Sequencing
This code demonstrates how to sequence addressable LEDs without using loops or `delay()`. This allows the checking of I/O ports or other work to be done while animating addressable LEDs.

## Driving Animation in the Loop
The INO file, **led.ino**, contains the main code. The key in this code segment is the `loop()`. The loop has code to check the status of four I/O ports (buttons) and also drives the animation by calling `animate()` on the current animation effect.

> The I/O ports (buttons) are being managed with a library called **[AceButton](https://github.com/bxparks/AceButton)**. This allows the code to be simplified and adds more functionality to the overall application. A portion of **led.ino** code is initializing the buttons.

Animations are added by creating a class that inherits from `IEffect` and draws a single "***frame***" each time `animate()` is called. The speed of the animation is controlled by setting the frame length (in ms) for each animation effect. The speed can be changed dynamically while the code is running. In order to facilitate large numbers of LEDs, it is important to design each animation efficiently. For example, only update LEDs that are changing in each frame rather than resetting and "*redrawing*" all LEDs on each frame update.

## Animation Effects
The files **IEffect.h** and **IEffect.cpp** define a base class for creating animations.

> The animations assume that the **[FastLED](https://fastled.io/)** library is being used.

The constructor for an animation effect requires the CRGB array used by the FastLED library, the count of LEDs and optionally the frame length in ms. If frame length is not specified, it defaults to `0` which disables the animation effect.

> Note frame length is the inverse of frame rate. 30 frames per second would yield a frame length of 33.33 milliseconds.

## Effects
There are two animation effects in the example. 

### SingleColorEffect.h
This effect turns one LED on at a time, starting at the first LED in the sequence and continuing to the last. When it arrives at the last LED, it starts over from the first LED. This animation works well when the LEDs are arranged in a ring.

The color can be specified in the constructor.

### TailEffect.h
This effect turns one LED on at a time, starting at the first LED in the sequence and continuing to the last. This effect also includes a tail where each subsequent LED in the tail decrease in brightness. The sequence of LEDs will appear to come out of the starting point and then disappear into the last LED position. After the last LED of the tail is displayed, the sequence repeats.

The color, tail length and tail fade factor can be specified in the constructor.

### SpinningRainbow.h
This animation effect will turn every LED in the LED strip on and create a spinning rainbow of color.

### ColorWheelStripeEffect.h
This animation creates a stripe the travels the from one end of the LED strip to the other changing colors as it travels.

The length of the stripe can be specified in the constructor.

### Supporting Files

#### Color.hand Color.cpp
The files **CHSL.h** and **CHSL.cpp** provide an HSL color class. HSL specifies colors in the form of hue, saturation and luminosity and is ideal for adjusting the brightness of a specific color. It is also useful for creating color wheel effects such as gradients and rainbows or spectrums.

#### Math.h and Math.cpp
The files **Math.h** and **Math.cpp** provides methods used by the color library.