#ifndef BME680SENSOR_H
#define BME680SENSOR_H

#include <Adafruit_BME680.h>
#include "pipeline.h"

class BME680Sensor
{
public:
    void init(uint8_t address = 0x77);
    void read();

    float getTemperature() { return temperature; }
    float getHumidity() { return humidity; }
    uint32_t getPressure() { return pressure; }
    uint32_t getGasResistance() { return gas_resistance; }

private:
    Adafruit_BME680 bme;
    const uint8_t SENSOR_ADDRESS = 0x77;

    float temperature;
    float humidity;
    uint32_t pressure;
    uint32_t gas_resistance;
};

#endif
