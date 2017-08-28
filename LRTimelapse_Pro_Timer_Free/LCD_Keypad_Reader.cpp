/*
  Pro-Timer Free
  Gunther Wegner
  http://gwegner.de
  http://lrtimelapse.com
  https://github.com/gwegner/LRTimelapse-Pro-Timer-Free

  Version 0.88: Thanks for Klaus Heiss (KH) for implementing the dynamic key rate
*/

#include "Arduino.h"
#include "LCD_Keypad_Reader.h"

static int DEFAULT_KEY_PIN = 0;

#define _display_standard_
// #define _display_alternative1_

#ifdef _display_standard_
  // The Sainsmart keypad uses a voltage divider to deliver a voltage
  // between 0 and 5 V that corresponds to the key being pressed in
  // order to use only a single input pin. The values below are from 0 to
  // 1023 because the Arduino uses a 10 bit resolution.
  /* Board introduced by G.W.   */
  static int DEFAULT_THRESHOLD = 50;   // KH: changed from 5 to 50 - more tolerance
  static int UPKEY_ARV = 144; // 0.720 V, that's read "analogue read value"
  static int DOWNKEY_ARV = 329; // 1.645 V
  static int LEFTKEY_ARV = 505; // 2.525 V
  static int RIGHTKEY_ARV = 0; // 0 V
  static int SELKEY_ARV = 742; // 3.710 V
  static int NOKEY_ARV = 1023; // 5.115 V
#endif

#ifdef _display_alternative1_
  // K.H.: My NEW Board (looks same as that one shown in project, but branded as: Open Source ELECTRONICS - Miroad
  //       has other voltage steps - here the values:  
  //  IF ONLY THE RIGHT-KEY IS RECOGNIZED ON YOUR BOARD,  TRY THIS VALUES 
  static int DEFAULT_THRESHOLD = 50;
  static int UPKEY_ARV = 99;
  static int DOWNKEY_ARV = 256;
  static int LEFTKEY_ARV = 410;
  static int RIGHTKEY_ARV = 0;
  static int SELKEY_ARV = 640;
  static int NOKEY_ARV = 1023;
#endif

LCD_Keypad_Reader::LCD_Keypad_Reader()
{
  _keyPin = DEFAULT_KEY_PIN;
  _threshold = DEFAULT_THRESHOLD;
  _curInput = NO_KEY;
  _curKey = NO_KEY;
  RepeatRate = keyRepeatRateSlow;
}

int LCD_Keypad_Reader::ActRepeatRate()
{
  RepeatRate -= keyRepeatRateStep;
  if (RepeatRate < keyRepeatRateHigh){
    RepeatRate =keyRepeatRateHigh;
  }
  return RepeatRate;
}

int LCD_Keypad_Reader::getKey()
{
  _curInput =  analogRead(_keyPin);
  _curKey = categorizeKey(_curInput);
  return _curKey;
}

int LCD_Keypad_Reader::categorizeKey(int analogKeyValue){
  int categorizedKeyValue = 0;

  if (analogKeyValue > UPKEY_ARV - _threshold && analogKeyValue < UPKEY_ARV + _threshold ){
      categorizedKeyValue = UP_KEY;
  }
  else if (analogKeyValue > DOWNKEY_ARV - _threshold && analogKeyValue < DOWNKEY_ARV + _threshold ){
      categorizedKeyValue = DOWN_KEY;
  }
  else if (analogKeyValue > RIGHTKEY_ARV - _threshold && analogKeyValue < RIGHTKEY_ARV + _threshold ){
      categorizedKeyValue = RIGHT_KEY;
  }
  else if (analogKeyValue > LEFTKEY_ARV - _threshold && analogKeyValue < LEFTKEY_ARV + _threshold ){
      categorizedKeyValue = LEFT_KEY;
  }
  else if (analogKeyValue > SELKEY_ARV - _threshold && analogKeyValue < SELKEY_ARV + _threshold ){
      categorizedKeyValue = SELECT_KEY;
  }
  else{
    categorizedKeyValue = NO_KEY;
  }

  return categorizedKeyValue;
}
