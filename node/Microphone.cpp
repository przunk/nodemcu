#include <Arduino.h>
#include "Common.h"
#include "Led.h"
#include "Microphone.h"

namespace Andrio {
  
  extern Led led;
  
  Microphone::Microphone(const int inputPin, const int triggerPin, const double zeroValue, const double doubleClapActivationCap)
    : MIC_INPUT_PIN(inputPin), MIC_TRIGGER_PIN(triggerPin), MICROPHONE_ZERO(zeroValue), MICROPHONE_DOUBLE_CLAP_ACTIVATION(doubleClapActivationCap) { 
    pinMode(MIC_INPUT_PIN, INPUT);
    pinMode(MIC_TRIGGER_PIN, OUTPUT);
  }
  
  double Microphone::checkMicSensor() const {
    const int sampleWindow = 25;
    unsigned long startMillis = millis(); 
    
    unsigned int peakToPeak = 0;      
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
       
    while (millis() - startMillis < sampleWindow) {
      int sample = analogRead(MIC_INPUT_PIN);
      if (sample < 1024) {
        if (sample > signalMax) {
          signalMax = sample; 
        }
        else if (sample < signalMin) {
          signalMin = sample; 
        }
      }
    }
    peakToPeak = signalMax - signalMin; 
    double volts = (peakToPeak * 3.3) / 1024.0; 
  
    return volts;
  }
  
  void Microphone::checkForDoubleClap(int clapTime, double micVolume) {
    int timeDiff = clapTime - lastClapTime; 
  
    if (micVolume > MICROPHONE_DOUBLE_CLAP_ACTIVATION) {
      lastClapTime = clapTime;
      
      printValue("Clap detected after time", timeDiff);
      
      if (timeDiff < 400 && timeDiff > 200){
        Serial.println("Double clap detected.");
        lastClapTime = 0;
        led.blinkLed();
      }
    }
  }
  
  bool Microphone::isMinimalVoltageCapReached(double voltage) const {
    return voltage > MICROPHONE_ZERO;
  }
}
