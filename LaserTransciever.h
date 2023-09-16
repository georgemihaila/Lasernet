#pragma once
#include <Arduino.h>
#include "presets.h"
#include "PhototransistorReceiver.h"
#include "Transceiver.h"
#include "Nullable.h"

class LaserTransciever
{
private:
  Transceiver *_positive;
  Transceiver *_negative;
  Nullable<bool> *_readResult = new Nullable<bool>();

  void _restState(int duration_us)
  {
    _positive->transmitBit(true, 0);
    _negative->transmitBit(true, 0);
    delayMicroseconds(duration_us);
  }

public:
  LaserTransciever() : LaserTransciever DEFAULT_LASER_CONFIG
  {
  }

  LaserTransciever(int pos_in_pin, int pos_out_pin, int neg_in_pin, int neg_out_pin)
  {
    _positive = new Transceiver(new Transmitter(pos_out_pin), new PhototransistorReceiver(pos_in_pin));
    _negative = new Transceiver(new Transmitter(neg_out_pin), new PhototransistorReceiver(neg_in_pin));
  }

  void transmitBit(bool bit, int duration_us)
  {
    if (bit)
    {
      _positive->transmitBit(true, 0);
      _negative->transmitBit(false, 0);
    }
    else
    {
      _positive->transmitBit(false, 0);
      _negative->transmitBit(true, 0);
    }
    delayMicroseconds(duration_us);
    _restState(duration_us);
  }

  Nullable<bool> *receiveBit()
  {
    bool pos = _positive->receiveBit();
    bool neg = _negative->receiveBit();

    if (pos != neg)
    {
      _readResult->hasValue = true;
      _readResult->value = pos;
    }
    else
    {
      _readResult->hasValue = false;
    }
    return _readResult;
  }
};