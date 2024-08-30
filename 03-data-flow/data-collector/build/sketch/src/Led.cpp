#line 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\src\\Led.cpp"
#include "Led.h"
#include "Arduino.h"

Led::Led(int pin)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Led::switchOn()
{
  digitalWrite(pin, HIGH);
}

void Led::switchOff()
{
  digitalWrite(pin, LOW);
};
