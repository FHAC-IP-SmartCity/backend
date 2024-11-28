#ifndef BH1750SENSOR_H
#define BH1750SENSOR_H

#include <BH1750.h>
#include "pipeline.h"

class BH1750Sensor
{
public:
    void init();
    void read();

private:
    // Use the BH1750 library to read the light level
    BH1750 lightMeter;
};

#endif
