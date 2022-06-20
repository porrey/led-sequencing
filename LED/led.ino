#include "IEffect.h"
#include <AceButton.h>
using namespace ace_button;

//
// reference the effects.
//
#include "SingleColorEffect.h"
#include "TailEffect.h"

//
// LED count; assumes all strips have the same number of LEDs.
//
#define LED_COUNT       16

//
// Define the data pin assignment for each of the 8 strips.
//
#define LED_PIN_1        2
#define LED_PIN_2        3
#define LED_PIN_3        4
#define LED_PIN_4        5
#define LED_PIN_5        6
#define LED_PIN_6        7
#define LED_PIN_7        8
#define LED_PIN_8        9

//
// Define the pins assigned to each button.
//
#define BUTTON_PIN_1    10
#define BUTTON_PIN_2    11
#define BUTTON_PIN_3    12
#define BUTTON_PIN_4    14

//
// Define a CRGB array to be shared by all strips. This allows the
// animation effect to be the same on each of the 8 strips. The color
// of each LED is set using this array and then the library uses this
// array when
//
CRGB _leds[LED_COUNT];

//
// Define the effects to be activated by the buttons.
//
const IEffect* _effect1 = new SingleColorEffect(_leds, LED_COUNT, 100, CRGB::Red);
const IEffect* _effect2 = new SingleColorEffect(_leds, LED_COUNT, 65, CRGB::Green);
const IEffect* _effect3 = new SingleColorEffect(_leds, LED_COUNT, 30, CRGB::Blue);
const IEffect* _effect4 = new TailEffect(_leds, LED_COUNT, 100, CRGB::White, 4);

//
// Places the effects into an array.
//
const IEffect* _effects[] = { _effect1, _effect2, _effect3, _effect4 };

//
// Using the AceButton library, define the 4 buttons.
//
AceButton _button1(BUTTON_PIN_1);
AceButton _button2(BUTTON_PIN_2);
AceButton _button3(BUTTON_PIN_3);
AceButton _button4(BUTTON_PIN_4);

//
// Forward reference for the button handler to prevent the
// compiler from becoming confused. When a buttons is
// pressed, this handler method will be called.
//
void handleEvent(AceButton*, uint8_t, uint8_t);

//
// Keep track of the current effect. This is the index
// to the effects array which selects the current animation.
//
int _currentEffect = 0;

//
// Create a flag to set the state of the LEDs. Default
// the state to "on".
//
bool _isOn = true;

//
// Create a flag to indicate the reset mode.
//
bool _reset = false;

void setup()
{
  //
  // Set up the serial port for debugging.
  //
  Serial.begin(115200);
  delay(250);

  //
  // Wait for serial port to connect.
  //
  while (!Serial) {}
  Serial.println("Serial port initialized.");

  //
  // Add the LEDs for each strip.
  //
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_3, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_4, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_5, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_6, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_7, GRB>(_leds, LED_COUNT);
  FastLED.addLeds<WS2812, LED_PIN_8, GRB>(_leds, LED_COUNT);
  Serial.println("FastLED initialization complete.");

  //
  // Initialize the buttons using an internal pull-up. This allows the button
  // to be connected directly between the data pin and ground.
  //
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  Serial.println("Button pin initialization complete.");

  //
  // Configure each button using ButtonConfig adding the
  // event handler and enabling additional events.
  //
  ButtonConfig* buttonConfig1 = _button1.getButtonConfig();
  buttonConfig1->setEventHandler(handleEvent);
  buttonConfig1->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig1->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);

  ButtonConfig* buttonConfig2 = _button2.getButtonConfig();
  buttonConfig2->setEventHandler(handleEvent);
  buttonConfig2->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig2->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);

  ButtonConfig* buttonConfig3 = _button3.getButtonConfig();
  buttonConfig3->setEventHandler(handleEvent);
  buttonConfig3->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig3->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);

  ButtonConfig* buttonConfig4 = _button4.getButtonConfig();
  buttonConfig4->setEventHandler(handleEvent);
  buttonConfig4->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig4->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);

  Serial.println("Button handler initialization complete.");
}

void loop()
{
  //
  // Check the state of each button.
  //
  _button1.check();
  _button2.check();
  _button3.check();
  _button4.check();

  //
  // Check the current state.
  //
  if (_isOn && !_reset)
  {
    //
    // Animate the current effect. If a change has been made the
    // method will return true.
    //
    if (_effects[_currentEffect]->animate())
    {
      //
      // Draw the current LEDs.
      //
      FastLED.show();
    }
  }
}

//
// This button handler will be called when the state of any
// button changes.
//
void handleEvent(AceButton* button, uint8_t eventType, uint8_t /* buttonState */)
{
  switch (eventType)
  {
    case AceButton::kEventPressed:
      //
      // Display the event on the serial port.
      //
      Serial.println("Button was pressed.");

      //
      // Reset the LED strips.
      //
      _effects[_currentEffect]->reset();

      //
      // Change the reset mode.
      //
      _reset = true;

      Serial.println("LED strips have been reset.");
      break;

    case AceButton::kEventLongPressed:
      //
      // Display the event on the serial port. This event is always
      // preceded by kEventPressed. The release event will be suppressed
      // after this event.
      //
      Serial.println("Button was long-pressed.");

      //
      // Change the reset mode.
      //
      _reset = false;

      //
      // Toggle the current running state.
      //
      _isOn = !_isOn;

      //
      // If the state is off, clear the strip.
      //
      if (!_isOn)
      {
        FastLED.clear();
        FastLED.show();
      }
      break;

    case AceButton::kEventReleased:
      //
      // Display the event on the serial port.
      //
      Serial.println("Button was released.");

      //
      // Set the current effect based on the button pushed. The
      // button is determined by checking hte PIN value.
      //
      uint16_t pin = button->getPin();
      Serial.print("Button pushed is on pin "); Serial.println(pin);

      switch (pin)
      {
        case BUTTON_PIN_1:
          _currentEffect = 0;
          break;
        case BUTTON_PIN_2:
          _currentEffect = 1;
          break;
        case BUTTON_PIN_3:
          _currentEffect = 2;
          break;
        case BUTTON_PIN_4:
          _currentEffect = 3;
          break;
      }

      //
      // Change the reset mode.
      //
      _reset = false;

      Serial.print("Current Effect Index is "); Serial.println(_currentEffect);
      break;
  }
}
