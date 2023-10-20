#include <FastLED.h>

#define NUM_LEDS 29
const byte DATA_PIN = 2;
const byte LDR_PIN = A2;
const int LIGHT_THRESHOLD = 600;
const int HYSTERESIS = 20;
CRGB leds[NUM_LEDS];

// Define the number of transition steps and the duration of each step
const int NUM_TRANSITION_STEPS = 100; // Adjust as needed
const int TRANSITION_DURATION_MS = 2000; // Adjust as needed

CRGBPalette16 currentPalette;
TBlendType currentBlending;

void setup() {
    Serial.begin(115200);
    pinMode(LDR_PIN, INPUT_PULLUP);
    LEDS.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    LEDS.setBrightness(120);
    FastLED.show();

    // Define a color palette for smooth transitions
    CRGBPalette16 targetPalette = RainbowColors_p; // You can use other palettes too
    currentPalette = targetPalette;
    currentBlending = LINEARBLEND;
}

void loop() {
    int lightValue = analogRead(LDR_PIN);

    if (lightValue > LIGHT_THRESHOLD + HYSTERESIS) {
        smoothColorTransition();
    } else {
        setColor(CRGB::Black);
        FastLED.show();
    }

    // Optional: Print light level for debugging
    Serial.print("Light Level: ");
    Serial.println(lightValue);
}

void smoothColorTransition() {
    for (int step = 0; step < NUM_TRANSITION_STEPS; step++) {
        uint8_t colorIndex = map(step, 0, NUM_TRANSITION_STEPS - 1, 0, 255);
        CRGB color = ColorFromPalette(currentPalette, colorIndex);
        setColor(color);
        FastLED.show();
        delay(TRANSITION_DURATION_MS / NUM_TRANSITION_STEPS);
    }
}

void setColor(CRGB color) {
    for (byte n = 0; n < NUM_LEDS; n++) {
        leds[n] = color;
    }
}
