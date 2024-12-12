namespace Andrio {

  class Led {
    private:
      const int INPUT_PIN;  
      unsigned long maxLightTime;
      unsigned long ledEnabledTime;
    public:
      Led(const int inputPin);
      void blinkLed();
      void turnOff();
      void turnOn(int ms);
      void refresh();
  };
}
