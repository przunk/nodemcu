#include "Led.h"
#include "Wifi.h"
#include "Ultrasonic.h"
#include "OTA.h"
#include "TemperatureHumidity.h"
#include "DS18B20.h"
#include "LM35.h"

using namespace Andrio;

const int LED_ON_TIME = 60 * 1000; // 60 s

Wifi wifi = { "WIFI_SSID", "WIFI_PASS", 0};
//OTA ota = { };
//Ultrasonic echo = { D1, D2 };
//Led led = { D1 };
//TemperatureHumidity temp = { D3 };
//DS18B20 dallas = { };
LM35 temp = { A0 };

void setup() {
  Serial.begin(115200);
  while (!Serial);

  setupWifiEvents();
  wifi.connect();
  //ota.initialize();
  //dallas.dallasBegin();
}

void loop() {
  wifi.refresh();
  //ota.refresh();
  //led.refresh();
  //dallas.dallasLoop();
  //echo.refresh();
  temp.refresh();

  double temperature = temp.getTemperature();
  Serial.print("Temperature = ");
  Serial.println(String(temperature, 2));

  //int val = temp.readData();
  //if (val == 0) {
  //  Serial.print("Temperature sensor output = " + String(val) + " ");
  //  Serial.print("Temperature = " + String(temp.getTemperature()) + " ");
  //  Serial.println("Humidity = " + String(temp.getHumidity()));
  //}
  
  //int distance = echo.checkUltrasonicSensor();
  //if (distance < 50){
  //  led.turnOn(1000);
  //}

  delay(100);
}

void setupWifiEvents(){
  wifi.addEvent("/lightOn", [&] () {
    //led.turnOn(LED_ON_TIME);
    wifi.sendOkResponse("Led turned on for " + String(LED_ON_TIME) + "ms");
  });
  wifi.addEvent("/lightOff", [&] () {
    //led.turnOff();
    wifi.sendOkResponse("Led turned off");
  });
  wifi.addEvent("/enableOTA", [&] () {
    //ota.enableOTA();
    wifi.sendOkResponse("OTA enabled for 15 seconds");
  });
}
