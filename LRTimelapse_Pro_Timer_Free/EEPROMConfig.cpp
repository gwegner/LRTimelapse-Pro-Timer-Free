/*
   Klaus Heiss
   www.elite.at
   Aug. 2017
*/

#include "EEPROMConfig.h"
#include <EEPROM.h>

void EEPParams::SerialPrintParams() {
  #ifdef debug
    String str = "";
    str = "Background brightness level = "; str += Params.BackgroundBrightnessLevel;  Serial.println(str);
    str = "Interval                    = "; str += Params.Interval;  Serial.println(str);
  #endif
}

boolean EEPParams::ParamsWrite() {
  #ifdef debug
    Serial.println("=== Write Params to EEPROM if changed ===");
  #endif
  EEPParamsStru epp;
  EEPROM.get(0,epp);
  if ( (Params.SumBytes                  != epp.SumBytes) ||    
       (Params.BackgroundBrightnessLevel != epp.BackgroundBrightnessLevel) ||
       (Params.Interval                  != epp.Interval) ||
       (Params.SumBytesXored             != epp.SumBytesXored) ) {
    crcOK();  // calcs & sets CRCSumBytes
    Params.SumBytes =      CRCSumBytes;
    Params.SumBytesXored = CRCSumBytes^0xFFFF;
    EEPROM.put(0,Params);
    #ifdef debug
      SerialPrintParams();
      Serial.println("wrote Params into EEPROM.");
    #endif
    return true;
  } else {
    #ifdef debug
      Serial.println("params didn't change.");
    #endif
    return false;
  }
}

boolean EEPParams::ParamsRead() {
  #ifdef debug
    Serial.println("=== Read Params from EEPROM ===");
  #endif
  // read Params fromEEPROM
  EEPROM.get(0,Params); 
  boolean retval = crcOK(); 
  if (retval) {
    #ifdef debug
      Serial.println("EEPROM Params (crc) OK");
    #endif
  } else {
    SerialPrintParams();
    Params = EEPParamsDefault;
    #ifdef debug
      Serial.println("EEPROM Params CRC WRONG - uses defaults");
    #endif
  }
  SerialPrintParams();
  return retval;
}

boolean EEPParams::crcOK() {
  int len = sizeof(Params);     //12abbbb12    len=9 -4 = 5
  byte * pb;
  pb = (byte *) & Params;
  pb += 2;
  CRCSumBytes = 0;
  for (int i=0; i < (len-4); i++) {
    CRCSumBytes += *pb++;
  }
  #ifdef debug
    Serial.println("=== Calc Params crc ===");
    String str = "";
    str = "Size Of Params= "; str += len;  Serial.println(str);
    
    str = "Params.SumBytes      = "; str += String(Params.SumBytes, HEX); Serial.println(str);
    str = "Calced SumBytes      = "; str += String(CRCSumBytes, HEX); Serial.println(str);
    
    str = "Params.SumXORedBytes = "; str += String(Params.SumBytesXored, HEX); Serial.println(str);
    str = "Calced SumXORedBytes = "; str += String(CRCSumBytes^0xFFFF, HEX); Serial.println(str);
  #endif
  boolean res = (CRCSumBytes == Params.SumBytes) && ((CRCSumBytes^0xFFFF) == Params.SumBytesXored);
  return res;
}

