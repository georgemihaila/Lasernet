#pragma once
#include "SimpleIODevice.h"
#include <Arduino.h>

class Receiver : public SimpleIODevice
{
public:
  Receiver(int pin) : SimpleIODevice(pin) {
    pinMode(pin, INPUT);
  }
  bool receiveBit()
  {
    return digitalRead(_pin) == HIGH ? true : false;
  }
};
