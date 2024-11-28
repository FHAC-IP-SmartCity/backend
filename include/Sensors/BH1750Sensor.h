#ifndef BH1750SENSOR_H
#define BH1750SENSOR_H

#include <BH1750.h>
#include "Sensors/SenosorData.h"
#include "pipeline.h"

class BH1750Sensor
{
public:
    void init();
    void read(SensorData &data);

private:
    BH1750 lightMeter;
};

#endif
