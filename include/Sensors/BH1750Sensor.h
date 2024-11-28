#ifndef BH1750SENSOR_H
#define BH1750SENSOR_H

#include <BH1750.h>
#include "pipeline.h"

class BH1750Sensor
{
public:
    // TODO: Add parameter
    void init();
    void read();
    float getLux() { return lux; }

private:
    // Use the BH1750 library to read the light level
    BH1750 lightMeter;
    float lux;
};

#endif
