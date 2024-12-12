#include <DallasTemperature.h>
#include <OneWire.h>

class DS18B20 {
  private:
    // Setup a oneWire instance to communicate with any OneWire devices
    OneWire oneWire;
    // Pass our oneWire reference to Dallas Temperature sensor 
    DallasTemperature sensors;
  public:
    DS18B20();
    void dallasBegin();
    void dallasLoop();
};
