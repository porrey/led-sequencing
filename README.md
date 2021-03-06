# LED Sequencing
This code demonstrates how to sequence addressable LEDs without using loops or `delay()`. This allows the checking of I/O ports or other work to be done while animating addressable LEDs. This is achieved through an animation process.

## Driving Animation in loop()
This animation described above is achieved by creating a process where each change to the LED strip is considered a single frame. The LED strip is updated one frame at a time in `loop()` by calling `animate()` on an effect. An effect defines what changes frame by frame. The effect also controls the frame rate by specifying the length of a frame in milliseconds.

## Changing Effects
Each effect is defined in a separate class. One or more effects can be defined but only one can be active. The active effect can be changed dynamically while the program is running.

The four push buttons are used to select a specific animation effect.

## Animation Effect Overview
The files **IEffect.h** and **IEffect.cpp** define a base class for creating animations.

> NOTE: The animations assume that the **[FastLED](https://fastled.io/)** library is being used.

The constructor for an animation effect requires the CRGB array used by the FastLED library, the count of LEDs and optionally the frame length in ms. If frame length is not specified, it defaults to `0` which disables the animation effect.

> NOTE: frame length is the inverse of frame rate. 30 frames per second would yield a frame length of 33 milliseconds.

Effects are create by inheriting from this base class and overriding `onAnimate()`. Other methods can be overridden depending on how much customization is necessary. Having all effects inherit from the same base class allows them to be easily stored in an array or similar structure so they can be selected/activated at run-time.

# Sample Code
## The INO
The INO file, **led.ino**, contains the main code. The key in this code segment is the `loop()`. The loop has code to check the status of four I/O ports (buttons) and also drives the animation by calling `animate()` on the current animation effect.

> NOTE: The I/O ports (buttons) are being managed with a library called **[AceButton](https://github.com/bxparks/AceButton)**. This allows the code to be simplified and adds more functionality to the overall application. A large portion of the **led.ino** `setup()` code is initializing the buttons.

Animations are added by creating a class that inherits from `IEffect` and draws a single "***frame***" each time `animate()` is called. The speed of the animation is controlled by setting the frame length (in ms) for each animation effect. The speed can be changed dynamically while the code is running. In order to facilitate large numbers of LEDs, it is important to design each animation efficiently. For example, only update LEDs that are changing in each frame rather than resetting and "*redrawing*" all LEDs on each frame update.

## Sample Effects
There are four animation effects in the example. 

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

## LED Strips
The sample codes defines 8 LED strips on 8 I/O ports all sharing the same LED array. This will drive all LEDs in exactly the same manner.

> NOTE: This feature has not been tested yet.

## Buttons
There are four buttons connected to four I/O pins. The connection is made between the pin and ground. The I/O port is initialized with am internal pull up resistor. 

> NOTE: If changing the button pins, be sure to either select a pin that supports `INPUT_PULLUP` or use an external pull up resistor (10K?? is usually a good value).

When any button is (short) pressed, the LED strip resets and pauses. When the button is release the effect associated with the button is activated and started immediately.

If any button is long pressed (held down for 1 second or longer), the LED strip will toggle between active and inactive state. When inactive, all the LEDs are off and the animation is paused. Pushing a button will have no effect when the strip is inactive. A second long press is required to reactivate the LED strip.

## Supporting Files

### Color.h and Color.cpp
The files **CHSL.h** and **CHSL.cpp** provide an HSL color class. HSL specifies colors in the form of hue, saturation and luminosity and is ideal for adjusting the brightness of a specific color. It is also useful for creating color wheel effects such as gradients, rainbows or spectrums.

### Math.h and Math.cpp
The files **Math.h** and **Math.cpp** provide methods used by the color library.
