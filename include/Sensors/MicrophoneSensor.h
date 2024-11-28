#ifndef MICROPHONESENSOR_H
#define MICROPHONESENSOR_H

#include <Arduino.h>
#include "Sensors/SenosorData.h"
#include "pipeline.h"

class MicrophoneSensor
{
public:
    void init();
    void read(SensorData &data);

private:
    const uint8_t MIC_PIN = 35; // ADC-Pin für das Mikrofon
};

#endif
