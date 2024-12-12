namespace Andrio {
  
  class HCSR04 {
    private:
      const int INPUT_PIN;
      const int TRIGGER_PIN;
    public:
      HCSR04(const int inputPin, const int triggerPin);
      int checkUltrasonicSensor() const;
      void refresh();
  };
}
