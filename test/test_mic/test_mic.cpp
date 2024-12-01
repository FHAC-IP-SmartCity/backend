#include <Arduino.h>

#include "Sensors/MicrophoneSensor.h"
#include "pipeline.h"

MicrophoneSensor micSensor;
uint16_t micValue = 0;

void setup()
{
    pipeline.open();
    micSensor.init();
}

void loop()
{
    // Daten aus dem Buffer holen
    micSensor.read();
    micValue = micSensor.getMicValue();
    pipeline.println(static_cast<int64_t>(micValue));

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}