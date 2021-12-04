#include <IRremote.hpp>
#include <FastLED.h>

////BEGIN IR DEFS
//row 1
const int CHANNEL_MINUS = 69;
const int CHANNEL = 70;
const int CHANNEL_PLUS = 71;

//row 2
const int BACK = 68;
const int FORWARD = 64;
const int PLAYPAUSE = 67;

//row 3
const int MINUS = 7;
const int PLUS = 21;
const int EQ = 9;

//row 4
const int ZERO = 22;
const int PLUS_100 = 25;
const int PLUS_200 = 13;

//row 5
const int ONE = 12;
const int TWO = 24;
const int THREE = 94;

//row 6
const int FOUR = 8;
const int FIVE = 28;
const int SIX = 90;

//row 7
const int SEVEN = 66;
const int EIGHT = 82;
const int NINE = 74;

//repeat
const int CONTINUE = 0;

//IR PIN
const int IR_PIN = 8;
////END IR DEFS

////BEGIN LED DEFS
#define LED_PIN     10
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];
int brightness = 125;
////END LED DEFS

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  Serial.println("Running");
}

void loop() {
  /* do effects here */
  leds[0] = CRGB(255, 0, 0);
  leds[1] = CRGB(0, 255, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[5] = CRGB(150, 0, 255);
  leds[9] = CRGB(255, 200, 20);
  leds[14] = CRGB(85, 60, 180);
  leds[19] = CRGB(50, 255, 20);

  while (!IrReceiver.isIdle());  // if not idle, wait till complete

  //check first for IR receiver
  if (IrReceiver.decode())
  {
    int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    doActionFromIR(command);
    IrReceiver.resume();
  }

  FastLED.show(); 
}

//LED FUNCTIONS
void adjustBrightness(int amount)
{
  Serial.println("adjustBrightness called");
  brightness = brightness + amount;
  if (brightness < 0)
  {
    brightness = 0;
  }
  if (brightness > 255)
  {
    brightness = 255;
  }
  Serial.println("Brightness adjusted to :" + String(brightness));
  FastLED.setBrightness(brightness);
}
//END LED FUNCTIONS

//IR FUNCTIONS
void doActionFromIR(int command)
{
  Serial.println("doActionFromIR");
  switch(command)
  {
    case CHANNEL_MINUS:
      //nextPattern();
      break;
    case CHANNEL:
      //nextPattern();
      break;
    case CHANNEL_PLUS:
      //nextPattern();
      break;
    case BACK:
      //nextPattern();
      break;
    case FORWARD:
      //nextPattern();
      break;
    case PLAYPAUSE:
      //nextPattern();
      break;
    case MINUS:
      Serial.println("MINUS");
      adjustBrightness(-5);
      break;
    case PLUS:
      Serial.println("PLUS");
      adjustBrightness(5);
      break;
    case EQ:
      //nextPattern();
      break;
    case ZERO:
      //nextPattern();
      break;
    case PLUS_100:
      //nextPattern();
      break;
    case PLUS_200:
      //nextPattern();
      break;
    case ONE:
      //nextPattern();
      break;
    case TWO:
      //nextPattern();
      break;
    case THREE:
      //nextPattern();
      break;
    case FOUR:
      //nextPattern();
      break;
    case FIVE:
      //nextPattern();
      break;
    case SIX:
      //nextPattern();
      break;
    case SEVEN:
      //nextPattern();
      break;
    case EIGHT:
      //nextPattern();
      break;
    case NINE:
      //nextPattern();
      break;
  }
}
//END IR FUNCTIONS
