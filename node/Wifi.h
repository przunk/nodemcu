#include <ESP8266WebServer.h>

namespace Andrio { 

  class Wifi {
    private:
      static const int HTTP_ERROR = 404;
      static const int HTTP_OK = 200;
      const String WIFI_SSID;
      const String WIFI_PASSWORD;
      const int RETRIES;
      void addStandardWebEvents();
      ESP8266WebServer webServer;
    public:
      Wifi(const String ssid, const String pass, const int retries);
      void connect();
      void refresh();
      void addEvent (String trigger, std::function<void ()> func);
      void sendErrorResponse(String errorMessage);
      void sendOkResponse(String message);
  //    template <typename C, typename... Args>
  //    void addEvent2 (String str, C&& c, Args&&... args) {
  //      webServer.on (str, [&] () {
  //          c (std::forward<Args> (args)...);
  //      });
  //    }

    //  wifi.addEvent2 ("/lightOn", &foo, 10);
  };
}
