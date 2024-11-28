#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <Arduino.h>
#include "pipeline.h"

class PhotoResistor
{
private:
    const uint8_t photoResistorPin = 36;
    const uint8_t redPin = 0;
    const uint8_t bluePin = 0;
    const uint8_t greenPin = 0;
    const int lightThreshold = 1500;
    int lux;

public:
    void init();
    void readData();
};

#endif
