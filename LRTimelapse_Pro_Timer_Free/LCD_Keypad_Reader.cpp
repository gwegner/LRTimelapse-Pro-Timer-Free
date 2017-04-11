#include "Arduino.h" 
#include "LCD_Keypad_Reader.h" 

static int DEFAULT_KEY_PIN = 0;  
static int DEFAULT_THRESHOLD = 5; 

// The Sainsmart keypad uses a voltage divider to deliver a voltage  
// between 0 and 5 V that corresponds to the key being pressed in  
// order to use only a single input pin. The values below are from 0 to  
// 1023 because the Arduino uses a 10 bit resolution. 
static int UPKEY_ARV = 144; // 0.720 V, that's read "analogue read value" 
static int DOWNKEY_ARV = 329; // 1.645 V 
static int LEFTKEY_ARV = 505; // 2.525 V 
static int RIGHTKEY_ARV = 0; // 0 V 
static int SELKEY_ARV = 742; // 3.710 V 
static int NOKEY_ARV = 1023; // 5.115 V 

LCD_Keypad_Reader::LCD_Keypad_Reader() 
{     
  _keyPin = DEFAULT_KEY_PIN; 
  _threshold = DEFAULT_THRESHOLD; 
  _curInput = NO_KEY; 
  _curKey = NO_KEY; 
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