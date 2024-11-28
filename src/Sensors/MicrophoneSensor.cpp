#include "Sensors/MicrophoneSensor.h"

void MicrophoneSensor::init(uint8_t micPin)
{
    this->micPin = micPin;
    pinMode(micPin, INPUT);
    pipeline.println("Mikrofonverstärker erfolgreich initialisiert.");
}

void MicrophoneSensor::read()
{
    micValue = analogRead(micPin);
}
