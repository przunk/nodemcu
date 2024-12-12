#include <Arduino.h>
#include "Led.h"

namespace Andrio {
  
  unsigned long maxLightTime = 60000;
  unsigned long ledEnabledTime = 0;
  
  Led::Led(const int inputPin) : INPUT_PIN(inputPin) {
    pinMode(INPUT_PIN, OUTPUT);
    //digitalWrite(INPUT_PIN, HIGH);
  }
  
  void Led::blinkLed() {
    digitalWrite(INPUT_PIN, HIGH);
    delay(250);
    digitalWrite(INPUT_PIN, LOW); 
  }
  
  void Led::turnOff() {
    //Serial.println("Turning the light off...");
    digitalWrite(INPUT_PIN, LOW); 
    
    ledEnabledTime = 0;
  }
  
  void Led::turnOn(int ms) {
    //Serial.println("Turning the light on for: " + String(ms) + " ms...");
    digitalWrite(INPUT_PIN, HIGH);
  
    maxLightTime = ms;
    ledEnabledTime = millis();
  }
  
  void Led::refresh() {
    if (ledEnabledTime > 0) {
      unsigned long timeLeft = maxLightTime - (millis() - ledEnabledTime);
      //Serial.println("Time left for LED: " + String(timeLeft));
      if (timeLeft >= maxLightTime) { 
        turnOff();
      }
    }
  }
}
