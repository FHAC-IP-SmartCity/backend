#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>
#include "pipeline.h"

class SensorData
{
public:
    float temperature = 0.0;
    float humidity = 0.0;
    float pressure = 0.0;
    float gasResistance = 0.0;
    int pirState = 0;
    int micValue = 0;
    float lux = 0.0;
    int tcrtValue = 0;

    void printData()
    {
        pipeline.println("=== Sensorwerte ===");
        pipeline.println("Temperatur: ");
        pipeline.println(temperature);
        pipeline.println(" °C");

        pipeline.println("Luftfeuchtigkeit: ");
        pipeline.println(humidity);
        pipeline.println(" %");

        pipeline.println("Luftdruck: ");
        pipeline.println(pressure);
        pipeline.println(" hPa");

        pipeline.println("Gas-Widerstand: ");
        pipeline.println(gasResistance);
        pipeline.println(" KΩ");

        pipeline.println("PIR-Sensor: ");
        pipeline.println(pirState ? "Bewegung erkannt" : "Keine Bewegung");

        pipeline.println("Mikrofonwert: ");
        pipeline.println(micValue);

        pipeline.println("Lichtstärke: ");
        pipeline.println(lux);
        pipeline.println(" lx");

        pipeline.println("TCRT5000-Sensorwert: ");
        pipeline.println(tcrtValue);
    }
};

#endif
