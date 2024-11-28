#ifndef BME680SENSOR_H
#define BME680SENSOR_H

#include <Adafruit_BME680.h>
#include "pipeline.h"

class BME680Sensor
{
public:
    void init();
    void read();

private:
    Adafruit_BME680 bme;
    const uint8_t SENSOR_ADDRESS = 0x77;
};

#endif
