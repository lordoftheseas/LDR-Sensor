#include <FastLED.h>

#define NUM_LEDS 29

const byte DATA_PIN = 2;
const byte ldrPin = A2;

const int lightThreshold = 600;
const int hysteresis = 20;

CRGB leds[NUM_LEDS];
CRGB color = {255, 255, 0};

void setup()
{
   Serial.begin(115200);
   pinMode(ldrPin, INPUT_PULLUP);
   LEDS.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
   LEDS.setBrightness(120);
   setColor(CRGB::Black);  // turn all LEDs off
   FastLED.show();
}

void loop()
{
   static unsigned long timer = 0;
   unsigned long interval = 200;
   if (millis() - timer >= interval)
   {
      timer = millis();
      int lightValue = analogRead(ldrPin);
      Serial.println(lightValue);
      if (lightValue > lightThreshold + hysteresis)
      {
         setColor(CRGB::White);
         FastLED.show();
      }
      else if (lightValue < lightThreshold - hysteresis)
      {
         setColor(CRGB::Black);
         FastLED.show();
      }
   }
}

void setColor(CRGB color)
{
   for (byte n = 0; n < NUM_LEDS; n++)
   {
      leds[n] = color;
   }
}