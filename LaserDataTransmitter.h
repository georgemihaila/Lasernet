#include "LaserTransciever.h";

// [1, 1] is the rest state; everything is relative to this state so we need to account for it
#define CLOCK_CORRECTION_FACTOR 2

class LaserDataTransmitter
{
private:
  LaserTransciever *_transceiver;
  int _delayPerBit;

public:
  LaserDataTransmitter(LaserTransciever *transceiver, int bitRate = 1)
  {
    _transceiver = transceiver;
    bitRate *= CLOCK_CORRECTION_FACTOR;
    _delayPerBit = bitRate == 0 ? 0 : 1000000 / bitRate;
  }

  void send_without_ack(short value)
  {
    for (int i = 0; i < 16; i++)
    {
      _transceiver->transmitBit(value & 1, _delayPerBit);
      value >>= 1;
    }
  }
};