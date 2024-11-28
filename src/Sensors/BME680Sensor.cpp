#include "Sensors/BME680Sensor.h"
#include <Wire.h>

void BME680Sensor::init()
{
    if (!bme.begin(SENSOR_ADDRESS))
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
        pipeline.println("Temperatur: ");
        pipeline.println(bme.temperature);
        pipeline.println(" °C, Luftfeuchtigkeit: ");
        pipeline.println(bme.humidity);
        pipeline.println(" %, Luftdruck: ");
        pipeline.println(bme.pressure / 100.0);
        pipeline.println(" hPa");
    }
    else
    {
        pipeline.println("Fehler beim Auslesen des BME680.");
    }
}
