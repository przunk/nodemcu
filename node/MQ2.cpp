#include <Arduino.h>
#include "MQ2.h"

namespace Andrio {

  MQ2::MQ2(const int inputPin) : INPUT_PIN(inputPin) {
    pinMode(INPUT_PIN, INPUT);
//    digitalWrite(INPUT_PIN, HIGH);
  }
  
  void MQ2::refresh() {
    float sensorValue = analogRead(A0);
    float sensorVolt = sensorValue / 1024 * 5.0;
    
    Serial.print("Gas sensor (MQ2) data = ");
    Serial.println(sensorVolt);
  }
}
