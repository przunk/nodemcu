namespace Andrio {

  class LM35 {
    private:
      const int INPUT_PIN;
      const float VREF = 3.0;
      const float RESOLUTION = VREF / 1023;
      double temperature;
    public:
      LM35(int inputPin);
      void refresh();
      double getTemperature();
  };
}
