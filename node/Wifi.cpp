#include "Wifi.h"
#include "Led.h"
#include "OTA.h"
#include <ESP8266WiFi.h>

namespace Andrio {

  extern Led led; 
  extern OTA ota;
  
  Wifi::Wifi(const String ssid, const String pass, const int retries) : WIFI_SSID(ssid), WIFI_PASSWORD(pass), RETRIES(retries) {
    //ESP8266WebServer webServer;
  }
  
  void Wifi::connect(){
    int tries = 0;
    WiFi.mode(WIFI_STA);
    while (WiFi.waitForConnectResult() != WL_CONNECTED && tries < RETRIES){
      Serial.println("Trying to connect to WiFi...");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      delay(2500);
      tries++;
    }
  
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.print("Connected to WiFi on address: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("Could not connect to WiFi.");
    }

    addStandardWebEvents();

    webServer.begin();
  }
  
  //void Wifi::addEvent(String eventTrigger, Action action) {
  //  webServer.on(eventTrigger, action);
  //}

  void Wifi::addStandardWebEvents() {
    addEvent("/echo", [&] () {
      sendOkResponse("ECHO...");
    });
  }
  
  void Wifi::addEvent(String trigger, std::function<void ()> func) {
      webServer.on(trigger, func);
  }

  void Wifi::sendErrorResponse(String errorMessage) {
    webServer.send(HTTP_ERROR, "text/plain", errorMessage);
  }

  void Wifi::sendOkResponse(String message) {
    webServer.send(HTTP_OK, "text/plain", message);
  }
  
  void Wifi::refresh() {
    webServer.handleClient();
  }
}
