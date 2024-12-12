#include <Arduino.h>
#include "HCSR04.h"

namespace Andrio {
  
  HCSR04::HCSR04(const int inputPin, const int triggerPin) : INPUT_PIN(inputPin), TRIGGER_PIN(triggerPin) {
    pinMode(INPUT_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
  }
  
  int HCSR04::checkUltrasonicSensor() const {
    // Clear the triggerPin
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin on HIGH state for 10 micro seconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    
    // Read the echoPin, return the sound wave travel time in microseconds
    int duration = pulseIn(INPUT_PIN, HIGH);
    
    // Calculate the distance
    int distance = duration * 0.034 / 2;
    
    return distance;
  }
  
  void HCSR04::refresh() {
    
  }
}
