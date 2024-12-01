#include <Arduino.h>

#include "Sensors/BME680Sensor.h"
#include "pipeline.h"

BME680Sensor BME;

uint32_t gasResistance;
float humidity;
uint32_t pressure;
float temperature;

void setup()
{
    pipeline.open();
    BME.init();
}

void loop()
{
    // Daten auslesen
    BME.read();

    // Daten speichern
    gasResistance = BME.getGasResistance();
    humidity = BME.getHumidity();
    pressure = BME.getPressure();
    temperature = BME.getTemperature();

    // Daten an den Server senden, wenn Daten vorhanden sind
    // Casting aufgrund von Entscheidungen der overloads
    pipeline.println(static_cast<int64_t>(gasResistance));
    pipeline.println(static_cast<double>(humidity));
    pipeline.println(static_cast<int64_t>(pressure));
    pipeline.println(static_cast<double>(temperature));

    delay(3000);
}