/*
  Pro-Timer Free
  Gunther Wegner
  http://gwegner.de
  http://lrtimelapse.com
  https://github.com/gwegner/LRTimelapse-Pro-Timer-Free

  Version 0.88: Thanks for Klaus Heiss (KH) for implementing the dynamic key rate
*/

#ifndef LCD_Keypad_Reader_h
#define LCD_Keypad_Reader_h

#include "Arduino.h"

#define SAMPLE_WAIT -1
#define NO_KEY 0
#define UP_KEY 3
#define DOWN_KEY 4
#define LEFT_KEY 2
#define RIGHT_KEY 5
#define SELECT_KEY 1

class LCD_Keypad_Reader
{
  public:
    LCD_Keypad_Reader();
    int getKey();
    int categorizeKey(int);
    int RepeatRate;
    int ActRepeatRate();
  private:
    int _keyPin;
    int _threshold;
    int _curInput;
    int _curKey;
};

const  int keySampleRate          = 100;      // ms between checking keypad for key

/* K.H: "Added KeyRepeatRateAcceleration" to   customize dynamic behavior */
const  int keyRepeatRateHighDelay = 500;      // delay for speeding up
const  int keyRepeatRateStep      =  60;      // speeding up steps
const  int keyRepeatRateSlow      = 500;      // SLOW speed when held, key repeats 1000 / keyRepeatRate times per second
const  int keyRepeatRateHigh      = 100;      // HIGH speed when held, key repeats 1000 / keyRepeatRate times per second


#endif
