#include "DHT11.h"

namespace Andrio {
  
  TemperatureHumidity::TemperatureHumidity (int inputPin) : INPUT_PIN(inputPin) {
      pinMode(INPUT_PIN, INPUT);
  }
  
  void TemperatureHumidity::refresh() {
    
  }
  
  double TemperatureHumidity::getTemperature() {
    return temperature;
  }
  
  double TemperatureHumidity::getHumidity() {
    return humidity;
  }
  
  int TemperatureHumidity::readData() {
      // READ VALUES
      int values = readSensor(DHTLIB_DHT11_WAKEUP);
      if (values != DHTLIB_OK) {
          humidity    = DHTLIB_INVALID_VALUE; // invalid value, or is NaN prefered?
          temperature = DHTLIB_INVALID_VALUE; // invalid value
          return values;
      }
  
      // CONVERT AND STORE
      //for (int i = 0; i < 5; i++){
      //    Serial.println("Bit " + String(i) + " value = " + String(bits[i]));
      //}
      humidity    = bits[0];
      temperature = bits[2] + (static_cast<double>(bits[3]) / 10.0);
  
      // TEST CHECKSUM
      // bits[1] && bits[3] both 0
      uint8_t sum = bits[0] + bits[2] + bits[3];
      if (bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;
  
      return DHTLIB_OK;
  }
  
  int TemperatureHumidity::readSensor(uint8_t wakeupDelay) {
      // INIT BUFFERVAR TO RECEIVE DATA
      uint8_t mask = 128;
      uint8_t idx = 0;
  
      // replace digitalRead() with Direct Port Reads.
      // reduces footprint ~100 bytes => portability issue?
      // direct port read is about 3x faster
      uint8_t bit = digitalPinToBitMask(INPUT_PIN);
      uint8_t port = digitalPinToPort(INPUT_PIN);
      volatile auto *PIR = portInputRegister(port);
  
      // EMPTY BUFFER
      for (uint8_t i = 0; i < 5; i++) bits[i] = 0;
  
      // REQUEST SAMPLE
      pinMode(INPUT_PIN, OUTPUT);
      digitalWrite(INPUT_PIN, LOW); // T-be 
      delay(wakeupDelay);
      digitalWrite(INPUT_PIN, HIGH);   // T-go
      delayMicroseconds(40);
      pinMode(INPUT_PIN, INPUT);
  
      // GET ACKNOWLEDGE or TIMEOUT
      uint16_t loopCntLOW = DHTLIB_TIMEOUT;
      while ((*PIR & bit) == LOW )  // T-rel
      {
          if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
      }
  
      uint16_t loopCntHIGH = DHTLIB_TIMEOUT;
      while ((*PIR & bit) != LOW )  // T-reh
      {
          if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
      }
  
      // READ THE OUTPUT - 40 BITS => 5 BYTES
      for (uint8_t i = 40; i != 0; i--)
      {
          loopCntLOW = DHTLIB_TIMEOUT;
          while ((*PIR & bit) == LOW )
          {
              if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
          }
  
          uint32_t t = micros();
  
          loopCntHIGH = DHTLIB_TIMEOUT;
          while ((*PIR & bit) != LOW )
          {
              if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
          }
  
          if ((micros() - t) > 40)
          { 
              bits[idx] |= mask;
          }
          mask >>= 1;
          if (mask == 0)   // next byte?
          {
              mask = 128;
              idx++;
          }
      }
      pinMode(INPUT_PIN, OUTPUT);
      digitalWrite(INPUT_PIN, HIGH);
  
      return DHTLIB_OK;
  }
}
