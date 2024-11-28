#include "Sensors/MicrophoneSensor.h"

void MicrophoneSensor::init()
{
    pinMode(MIC_PIN, INPUT);
    pipeline.println("Mikrofonverstärker erfolgreich initialisiert.");
}

void MicrophoneSensor::read(SensorData &data)
{
    data.micValue = analogRead(MIC_PIN);
}
