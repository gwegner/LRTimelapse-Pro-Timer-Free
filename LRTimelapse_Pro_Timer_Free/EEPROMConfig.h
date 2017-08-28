/*
   Klaus Heiss
   www.elite.at
   Aug. 2017
*/

#ifndef __EEPROM_Config__
#define __EEPROM_Config__

#include <Arduino.h>

// #define debug
#undef debug

//                                        N/A   BGL:0..5  interval   N/A
#define EEPParamsDefault (EEPParamsStru) { 0,          4,      4.0,   0 };

struct EEPParamsStru {
  unsigned int SumBytes;                      // 2
  byte         BackgroundBrightnessLevel;     // 1
  float        Interval;                      // 4
  unsigned int SumBytesXored;                 // 2
};                                            // 9 Bytes

class EEPParams {
  private:
    unsigned int CRCSumBytes;
    boolean crcOK();
    void SerialPrintParams();
  public:
    EEPParamsStru Params;
    boolean ParamsRead();
    boolean ParamsWrite();
    
};

#endif
