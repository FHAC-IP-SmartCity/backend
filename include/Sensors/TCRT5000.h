#ifndef TCRT5000SENSOR_H
#define TCRT5000SENSOR_H

#include <Arduino.h>
#include "pipeline.h"

class TCRT
{
public:
    void init(uint8_t pin);
    void read();
    int getTCRTValue()
    {
        if (tcrtValue >= 4095)
        {
            tcrtValue = 3000;
        }

        return tcrtValue;
    }

private:
    int tcrtValue;
    uint8_t pin;
};

#endif
