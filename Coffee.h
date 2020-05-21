#ifndef Coffee_h
#define Coffee_h

#include "Arduino.h"

class LM35 {
  private:
    int temp_pin;
  public:
    LM35();
    LM35(int);
    float get_temp();
};

class US_Sensor {
  private:
    int echo;
    int trigger;

  public:
    US_Sensor();
    US_Sensor(int, int);
    float range();
    bool perc(int);
};

class Motor {
  private:
    int M;
    int EN;

  public:
    Motor(int);
    void motor_start(int);
};

class Level_Sensor {
  private:
    int level_pin;
  public:
    Level_Sensor();
    Level_Sensor(int);
    bool milk_empty();
};

class IR_Sensor {
  private:
    int IR_pin;
  public:
    IR_Sensor();
    IR_Sensor(int);
    bool coffee_empty();
};

#endif
