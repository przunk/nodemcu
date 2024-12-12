#include "DS18B20.h"

//// GPIO where the DS18B20 is connected to
//const int oneWireBus = 4;     
//
//// Setup a oneWire instance to communicate with any OneWire devices
//OneWire oneWire(oneWireBus);
//
//// Pass our oneWire reference to Dallas Temperature sensor 
//DallasTemperature sensors(&oneWire);
DS18B20::DS18B20() {
   oneWire = { 4 };
   sensors = { &oneWire };
}

void DS18B20::dallasBegin(){
  sensors.begin();
}

void DS18B20::dallasLoop(){
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  if (temperatureC > 0) {
    Serial.print("Temperature = ");
    Serial.print(temperatureC);
    Serial.println(" ºC");
  }
}
