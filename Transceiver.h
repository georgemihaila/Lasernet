#pragma once
#include "Transmitter.h"
#include "Receiver.h"

class Transceiver
{
private:
  Transmitter *_transmitter;
  Receiver *_receiver;

public:
  Transceiver(Transmitter *transmitter, Receiver *receiver)
  {
    _transmitter = transmitter;
    _receiver = receiver;
  }

  void transmitBit(bool bit, int duration_us)
  {
    _transmitter->transmitBit(bit, duration_us);
  }

  bool receiveBit()
  {
    return _receiver->receiveBit();
  }
};