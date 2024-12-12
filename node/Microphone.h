namespace Andrio {
  
  class Microphone { 
    private:
      const int MIC_INPUT_PIN;
      const int MIC_TRIGGER_PIN;
      const double MICROPHONE_ZERO;
      const double MICROPHONE_DOUBLE_CLAP_ACTIVATION;
      int lastClapTime = 0;
    public:
      Microphone(const int inputPin, const int triggerPin, const double zeroValue, const double doubleClapActivationCap);
      double checkMicSensor() const;
      void checkForDoubleClap(int clapTime, double micVolume);
      bool isMinimalVoltageCapReached(double voltage) const;
  };
}
