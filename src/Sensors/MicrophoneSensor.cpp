#include "Sensors/MicrophoneSensor.h"

void MicrophoneSensor::init()
{
    pinMode(MIC_PIN, INPUT);
    Serial.println("Mikrofonverstärker erfolgreich initialisiert.");
}

void MicrophoneSensor::read(SensorData &data)
{
    data.micValue = analogRead(MIC_PIN);
}
