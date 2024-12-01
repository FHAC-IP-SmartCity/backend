#ifndef BH1750SENSOR_H
#define BH1750SENSOR_H

#include <BH1750.h>
#include "pipeline.h"

class BH1750Sensor
{
public:
    // TODO: Add parameter
    void init(uint8_t address = 0x23);
    void read();
    float getLux() { return lux; }

private:
    // Nutzung des BH1750-Sensors
    BH1750 lightMeter;
    float lux;
};

#endif
