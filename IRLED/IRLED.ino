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
int mode = 0;
int maxMode = 1;
uint8_t hue = 120;
uint8_t hueIncr = 1;
int changeDelay = 50;
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
  performMode();
  
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
void performMode()
{
  EVERY_N_MILLIS_I(timingObj, changeDelay) 
  {
    switch (mode)
    {
      case 0:
        singleColour();
        break;
      case 1:
        rainbow();
        break;
    }
    timingObj.setPeriod(changeDelay); 
    FastLED.setBrightness(brightness);
  }
}

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
}

void adjustMode(int amount)
{
  mode = mode + amount;
  if (mode < 0)
  {
    mode = maxMode;
  }
  if (mode > maxMode)
  {
    mode = 0;
  }
}

void adjustSpeed(int amount)
{
  changeDelay = changeDelay + amount;
  if (changeDelay < 10)
  {
    changeDelay = 10;
  }
  if (changeDelay > 5000)
  {
    changeDelay = 5000;
  }
  Serial.println("adjustSpeed("+String(amount)+" Speed: "+String(changeDelay));
}

////LED MODES
void singleColour()
{
  //Serial.println("singleColour execute");
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
  hue = hue + hueIncr;
}

void rainbow()
{
  //Serial.println("rainbow execute");
  uint8_t hueJump = (255 / NUM_LEDS) * hueIncr;
  fill_rainbow(leds, NUM_LEDS, hue, hueJump);
  hue = hue + hueIncr;
}
////END LED MODES
//END LED FUNCTIONS

//IR FUNCTIONS
void doActionFromIR(int command)
{
  Serial.println("doActionFromIR");
  switch(command)
  {
    case CHANNEL_MINUS:
      adjustMode(-1);
      break;
    case CHANNEL:
      //nextPattern();
      break;
    case CHANNEL_PLUS:
      adjustMode(1);
      break;
    case BACK:
      adjustSpeed(10);
      break;
    case FORWARD:
      adjustSpeed(-10);
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
