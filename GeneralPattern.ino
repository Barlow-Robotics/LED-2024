#include <FastLED.h>

#define NUM_LEDS  47
#define LED_PIN   2

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( greenblue_gp ) { 
  0,   137,  255, 0,
  46,  0,  155,  0,
  179, 12, 250, 0,
  255, 66, 255, 60
};

uint8_t currentMode = 0x00;

CRGBPalette16 greenblue = greenblue_gp;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  //Fill the colorIndex array with random numbers
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
}

void loop() {
  currentMode = 4;
  bool redAlliance = (currentMode & 0b00000001) == 0b00000001; // 0b00000001 IF 00000001 IS ENABLED --> THEN RED
  bool blueAlliance = (currentMode & 0b00000001) != 0b00000001;  // 0b00000001 IF 00000001 NOT ENABLED --> THEN BLUE
  bool enabled = (currentMode & 0b00001000) == 0b00001000;
  bool isShooting = currentMode & 0b00000001 == 0b00000001;
  // bool (isShooting = currentMode % 2) == 1; 
  Serial.println(currentMode);
  bool autoActivated = (currentMode & 0b00000100) == 0b00000100;
  // bool noteLoaded = (currentMode & ___) == ____; // oranage

  //Creat a sin wave with period of 2 seconds (30bpm) to change the brightness of the strip
  uint8_t sinBeat = beatsin8(30, 50, 255, 0, 0);
  
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i], sinBeat);
  }
  
  EVERY_N_MILLISECONDS(5){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
    // while (Serial.available() > 0) {
    //   uint8_t incomingByte = Serial.read();
    //   if (incomingByte >= 1 && incomingByte <= 15) {
    //     currentMode = incomingByte;
    //   }
    // }
    FastLED.show();
  }
}