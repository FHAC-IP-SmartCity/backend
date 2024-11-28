#include "Sensors/TCRT5000Sensor.h"

void TCRT5000Sensor::init(uint8_t pin)
{
    pinMode(pin, INPUT);
    pipeline.println("TCRT5000 Infrarotsensor erfolgreich initialisiert.");
}

void TCRT5000Sensor::read(uint8_t pin)
{
    tcrtValue = analogRead(pin);
    pipeline.println("TCRT5000 Infrarotsensorwert: ");
    pipeline.println(tcrtValue);
}
