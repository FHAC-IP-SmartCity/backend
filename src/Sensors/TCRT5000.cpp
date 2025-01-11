#include "Sensors/TCRT5000.h"

void TCRT::init(uint8_t pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    Serial.println("TCRT5000 Infrarotsensor erfolgreich initialisiert.");
}

void TCRT::read()
{
    tcrtValue = analogRead(pin);
}
