#include "Sensors/BME680Sensor.h"
#include <Wire.h>

void BME680Sensor::init()
{
    if (!bme.begin(SENSOR_ADDRESS))
    {
        Serial.println("BME680 konnte nicht initialisiert werden.");
        while (1)
            ;
    }
    Serial.println("BME680 erfolgreich initialisiert!");
}

void BME680Sensor::read(SensorData &data)
{
    if (bme.performReading())
    {
        data.temperature = bme.temperature;
        data.humidity = bme.humidity;
        data.pressure = bme.pressure / 100.0;
        data.gasResistance = bme.gas_resistance / 1000.0;
    }
    else
    {
        Serial.println("Fehler beim Auslesen des BME680.");
    }
}
