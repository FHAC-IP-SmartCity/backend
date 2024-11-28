#ifndef TCRT5000SENSOR_H
#define TCRT5000SENSOR_H

#include <Arduino.h>
#include "pipeline.h"

class TCRT5000Sensor
{
public:
    void init(uint8_t pin = 32);
    void read();
    int getTCRTValue() { return tcrtValue; }

private:
    uint8_t pin;
    int tcrtValue;
};

#endif
