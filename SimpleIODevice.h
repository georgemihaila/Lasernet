#pragma once
class SimpleIODevice
{
protected:
  int _pin;
  SimpleIODevice(int pin)
  {
    _pin = pin;
  }
};