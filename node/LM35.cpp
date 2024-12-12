#include <Arduino.h>
#include "LM35.h"

namespace Andrio {

  LM35::LM35(int inputPin) : INPUT_PIN(inputPin) {
    
  }

  double LM35::getTemperature() {
    double temperature;
  }

  void LM35::refresh() {
    temperature = (analogRead(INPUT_PIN) * RESOLUTION) * 100;
  }
}
