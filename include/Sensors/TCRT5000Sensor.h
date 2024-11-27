#ifndef TCRT5000SENSOR_H
#define TCRT5000SENSOR_H

#include <Arduino.h>
#include "Sensors/SenosorData.h"

class TCRT5000Sensor
{
public:
    void init();
    void read(SensorData &data);

private:
    const uint8_t SENSOR_PIN = 32; // Pin für den TCRT5000
};

#endif
