#include <Arduino.h>

#define READINGS_PER_SECOND 15
#define SAMPLES_PER_READING 20
#define DELAY_US (1000000 / (SAMPLES_PER_READING * READINGS_PER_SECOND))

#define POS_IN 32
#define POS_OUT 21

#define NEG_IN 33
#define NEG_OUT 22

#define DEFAULT_LASER_CONFIG (POS_IN, POS_OUT, NEG_IN, NEG_OUT)