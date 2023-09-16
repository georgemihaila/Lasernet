#include "presets.h"
#include "LaserTransciever.h"
#include "LaserDataTransmitter.h"

LaserTransciever* _transciever = new LaserTransciever();
LaserDataTransmitter* _transmitter = new LaserDataTransmitter(_transciever, 5);

void setup()
{
  Serial.begin(115200);
}

bool laserOn = false;

void loop()
{
  _transmitter->send_without_ack(random());
  /*
  Nullable<bool> *value = _transciever->receiveBit();
  if (value->hasValue){
    Serial.println(value->value?"1":"0");
  }
  else{
    Serial.println("No value");
  }*/
}