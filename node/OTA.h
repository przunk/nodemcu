namespace Andrio {

  class OTA {
    private: 
      bool otaEnabled;
      unsigned long startTime;
      const unsigned long OTA_HANDLE_TIME = 15000; // 15s
    public:
      OTA();
      void initialize();
      void checkOTA();
      void enableOTA();
      void refresh();
  };
}
