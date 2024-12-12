#include "Common.h"

namespace Andrio {
  
  void printValue(String prefix, int value){
    Serial.print(prefix);
    Serial.print(" = ");
    Serial.println(String(value));
  }
  
  void printValue(String prefix, double value){
    Serial.print(prefix);
    Serial.print(" = ");
    Serial.println(String(value, 5));
  }
}
