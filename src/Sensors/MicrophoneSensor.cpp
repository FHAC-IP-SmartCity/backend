#include "Sensors/MicrophoneSensor.h"

void MicrophoneSensor::init()
{
    pinMode(MIC_PIN, INPUT);
    pipeline.println("Mikrofonverstärker erfolgreich initialisiert.");
}

void MicrophoneSensor::read()
{
    micValue = analogRead(MIC_PIN);
    pipeline.println("Mikrofonwert: ");
    pipeline.println(micValue);
}
