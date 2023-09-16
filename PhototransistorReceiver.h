#pragma once
#include "Receiver.h"
#include <Arduino.h>
#include "PhotoCalibrator.h"

class PhototransistorReceiver : public Receiver
{
private:
  PhotoCalibrator* _calibrator;

public:
  PhototransistorReceiver(int pin) : Receiver(pin)
  {
    _calibrator = new PhotoCalibrator(pin);
  }
  
  bool receiveBit()
  {
    return _calibrator->withinBounds(analogRead(_pin));
  }
};