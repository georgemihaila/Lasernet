#define CALIBRATION_DURATION_MS 500
#define SAMPLES 100
#define SAMPLING_TIME_uS ((CALIBRATION_DURATION_MS * 1000) / SAMPLES)
#define _Z_ 1.96

struct Bounds {
  int min;
  int max;
};

/*
 * A class for auto-calibrating photoresistor values; since we don't know the interval the sensor floats at, we need to determine it and adjust it when necessary.
*/
class PhotoCalibrator
{
private:
  //ESP stuff
  int _pin;

  //Statistics stuff
  int _readings[SAMPLES];
  int _mean = 0;
  int _sd = 0;

  //Relevant for class logic
  bool _calibrated = false;
  Bounds _bounds = {
    0, 0
  };

public:
  PhotoCalibrator(int pin)
  {
    _pin = pin;
  }

  /*
   * Inspired by the method I used here - https://github.com/georgemihaila/esp8266-power-meter/blob/master/esp8266.ino
   * A "reading" is a value that is off by more than two standard deviations away from the mean.
  */
  void calibrate(){
    int sum = 0;
    for (int i = 0; i < SAMPLES; i++) {
      _readings[i] = analogRead(_pin);
      sum += _readings[i];
      delayMicroseconds(SAMPLING_TIME_uS);
    }
    _mean = sum / SAMPLES;
    double variance = 0;
    for (int i = 0; i < SAMPLES; i++){
      variance += (_readings[i] - _mean) * (_readings[i] - _mean);
    }
    _sd = variance / SAMPLES;
    int dev_offset = _Z_ * 2 * _sd;
    _bounds.min = _mean - dev_offset;
    _bounds.max = _mean + dev_offset;
    _calibrated = true;
  }

  bool isCalibrated(){
    return _calibrated;
  }

  Bounds getBounds(){
    if (!isCalibrated()){
      calibrate();
    }
    return _bounds;
  }

  bool withinBounds(int value){
    return value > _bounds.min && value < _bounds.max;
  }
};