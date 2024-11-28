#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <Arduino.h>
#include "pipeline.h"

class PhotoResistor
{
private:
    const int lightThreshold = 1500;
    int lux;
    uint8_t pin;

public:
    void init(uint8_t pin = 36);
    void readData();
    int getLux() { return lux; }
};

#endif
