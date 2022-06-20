# LED Sequencing
This code demonstrates how to sequence addressable LEDs without using loops or `delay()`. This allows the checking of I/O ports or other work to be done while animating addressable LEDs.

## Driving Animation in the Loop
The INO file, **led.ino**, contains the main code. The key in this code segment is the `loop()`. The loop has code to check the status of four I/O ports (buttons) and also drives the animation by calling `animate()` on the current animation effect.

> The I/O ports (buttons) are being managed with a library called **[AceButton](https://github.com/bxparks/AceButton)**. This allows the code to be simplified and adds more functionality to the overall application. A portion of **led.ino** code is initializing the buttons.

Animations are added by creating a class that inherits from `IEffect` and draws a single "***frame***" each time `animate()` is called. The speed of the animation is controlled by setting the frame length (in ms) for each animation effect. The speed can be changed dynamically while the code is running. In order to facilitate large numbers of LEDs, it is important to design each animation efficiently. For example, only update LEDs that are changing in each frame rather than resetting and "*redrawing*" all LEDs on each frame update.

## Animation Effects
The files **IEffect.h** and **IEffect.cpp** define a base class for creating animations.

> The animations assume that the **[FastLED](https://fastled.io/)** library is being used.

The constructor for an animation effect requires the CRGB array used by the FastLED library, the count of LEDs and optionally the frame rate. If Frame rate is not specified, it defaults to `0` which disables the animation effect.

## Effects
There are two animation effects in the example. 

### SingleColorEffect.h
This effect turns one LED on at a time, starting at the first LED in the sequence and continuing to the last. When it arrives at the last LED, it starts over from the first LED. This animation works well when the LEDs are arranged in a ring.

The color can be specified in the constructor.

### TailEffect.h
This effect turns one LED on at a time, starting at the first LED in the sequence and continuing to the last. This effect also includes a tail where each subsequent LED in the tail decrease in brightness. The sequence of LEDs will appear to come out of the starting point and then disappear into the last LED position. After the last LED of the tail is displayed, the sequence repeats.

The color and tail length can be specified in the constructor.

### Color.h
The files **color.h** and **color.cpp** provide some additional functions for converting colors between RGB and HSL. For example, this library supports the need to change the brightness of an RGB color. There are also methods for get colors from a HUE color wheel.