#ifndef MICROPHONESENSOR_H
#define MICROPHONESENSOR_H

#include <Arduino.h>
#include "pipeline.h"

class MicrophoneSensor
{
public:
    void init(uint8_t pin = 35);
    void read();
    uint16_t getMicValue() { return micValue; }

private:
    uint16_t micValue;
    uint8_t micPin;
};

#endif
