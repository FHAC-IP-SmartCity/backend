#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>

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
        Serial.println("=== Sensorwerte ===");
        Serial.print("Temperatur: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Luftfeuchtigkeit: ");
        Serial.print(humidity);
        Serial.println(" %");

        Serial.print("Luftdruck: ");
        Serial.print(pressure);
        Serial.println(" hPa");

        Serial.print("Gas-Widerstand: ");
        Serial.print(gasResistance);
        Serial.println(" KΩ");

        Serial.print("PIR-Sensor: ");
        Serial.println(pirState ? "Bewegung erkannt" : "Keine Bewegung");

        Serial.print("Mikrofonwert: ");
        Serial.println(micValue);

        Serial.print("Lichtstärke: ");
        Serial.print(lux);
        Serial.println(" lx");

        Serial.print("TCRT5000-Sensorwert: ");
        Serial.println(tcrtValue);
    }
};

#endif
