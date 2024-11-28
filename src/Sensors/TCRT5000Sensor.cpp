#include "Sensors/TCRT5000Sensor.h"

void TCRT5000Sensor::init()
{
    pinMode(SENSOR_PIN, INPUT);
    pipeline.println("TCRT5000 Infrarotsensor erfolgreich initialisiert.");
}

void TCRT5000Sensor::read(SensorData &data)
{
    data.tcrtValue = analogRead(SENSOR_PIN);
}
