#include "Sensors/BME680Sensor.h"
#include <Wire.h>

void BME680Sensor::init(uint8_t address)
{
    if (!bme.begin(address))
    {
        pipeline.println("BME680 konnte nicht initialisiert werden.");
        while (1)
            ;
    }
    pipeline.println("BME680 erfolgreich initialisiert!");
}

void BME680Sensor::read()
{
    if (bme.performReading())
    {
        temperature = bme.temperature;
        humidity = bme.humidity;
        pressure = bme.pressure;
        gas_resistance = bme.gas_resistance;
    }
    else
    {
        pipeline.println("Fehler beim Auslesen des BME680.");
    }
}
