#include "OTA.h"
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

namespace Andrio { 
  
  OTA::OTA(){
    otaEnabled = false;
    initialize();
  }
  
  void OTA::initialize(){
    ArduinoOTA.setPassword((const char *)"121212");
    
    ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else { // U_SPIFFS
        type = "filesystem";
      }
  
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nOTA ended");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
      }
    });
    ArduinoOTA.begin();
  }
  
  void OTA::refresh() {
    if (otaEnabled) {
      ArduinoOTA.handle();
      unsigned long nowTime = millis();
      if (nowTime - startTime > OTA_HANDLE_TIME) {
        Serial.println("Disable OTA...");
        otaEnabled = false;
      }
    }
  }
  
  void OTA::enableOTA(){
    startTime = millis();
    otaEnabled = true;
  }
}
