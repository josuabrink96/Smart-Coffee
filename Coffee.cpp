#include "Coffee.h"

IR_Sensor::IR_Sensor() {
  IR_pin = 29;
}

IR_Sensor::IR_Sensor(int pin) {
  IR_pin = pin;
}

bool IR_Sensor::coffee_empty() {
  return digitalRead(IR_pin) == 1;
}

US_Sensor::US_Sensor() {
  echo = 22;
  trigger = 23;
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
}

US_Sensor::US_Sensor(int e, int t) {
  echo = e;
  trigger = t;
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
}

// determine water level
float US_Sensor::range() {
  // Speed of sound
  const float S_SPEED = 0.034; 
  int distance;
  // Time it takes to pick up US pulses
  float duration; 

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * S_SPEED / 2;

  return distance;
}

//converting water level to a %
bool US_Sensor::perc(int empty) {
  return (((empty - range()) / empty) * 100) > 50;
}

LM35::LM35() {
  temp_pin = 24;
  pinMode(temp_pin, INPUT);
}

LM35::LM35(int t) {
  temp_pin = t;
  pinMode(temp_pin, INPUT);
}

float LM35::get_temp() {
  const int VOLTAGE = 5000;
  const int TEMP_DIVISIONS = 10;
  const float BITS = 1024.0;

  float val = analogRead(temp_pin);
  float mv = (val / BITS) * VOLTAGE;
  float celcius = mv / TEMP_DIVISIONS;
  return celcius;
}

Motor::Motor(int m) {
  M = m;
  pinMode(M, OUTPUT);
}

void Motor::motor_start(int s) {
  digitalWrite(M, s);
}

Level_Sensor::Level_Sensor() {
  level_pin = 25;
}

Level_Sensor::Level_Sensor(int lp) {
  level_pin = lp;
}

bool Level_Sensor::milk_empty() {
    return digitalRead(level_pin) == 1;
}
