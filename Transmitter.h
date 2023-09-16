#pragma once
#include "SimpleIODevice.h"
#include "Receiver.h"

class Transmitter : public SimpleIODevice
{
public:
  Transmitter(int pin) : SimpleIODevice(pin)
  {
    pinMode(pin, OUTPUT);
  }
  void transmitBit(bool bit, int duration_us)
  {
    digitalWrite(_pin, bit);
    if (duration_us > 0)
      delayMicroseconds(duration_us);
  }
  void safeTransmitBit(bool bit, int duration_us, int max_attempts, Receiver neg_receiver)
  {
    int attempts = 0;
    while (attempts < max_attempts)
    {
      transmitBit(bit, 0);
      if (neg_receiver.receiveBit() != bit)
      {
        break;
      }
      delayMicroseconds(duration_us);
      attempts++;
    }
  }
};
