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
  private: 
    int _keyPin; 
    int _threshold; 
    int _curInput; 
    int _curKey; 
}; 

#endif