#include <Arduino.h>

namespace Andrio {
  
  #define DHT_LIB_VERSION "0.1.14"
  
  #define DHTLIB_OK                0
  #define DHTLIB_ERROR_CHECKSUM   -1
  #define DHTLIB_ERROR_TIMEOUT    -2
  #define DHTLIB_INVALID_VALUE    -999
  
  #define DHTLIB_DHT11_WAKEUP     18
  #define DHTLIB_DHT_WAKEUP       1
  
  #define DHTLIB_TIMEOUT (F_CPU/40000)
  
  class TemperatureHumidity {
    private:
      const int INPUT_PIN;  
      uint8_t bits[5];
      int readSensor(uint8_t wakeupDelay);
      double humidity;
      double temperature;
    public:
      TemperatureHumidity(int inputPin);
      int readData();
      double getTemperature();
      double getHumidity();    
      void refresh();
  };
}
