#include <Arduino.h>

#include "Sensors/TCRT5000Sensor.h"
#include "pipeline.h"
TCRT5000Sensor TCRT;

int TCRTVal = 0;

void setup()
{
    pipeline.open();
    TCRT.init();
}

void loop()
{
    // Daten von den Sensoren auslesen
    TCRT.read();

    // Daten aus dem Buffer holen
    TCRTVal = TCRT.getTCRTValue();

    // Daten an den Server senden, wenn Daten vorhanden sind
    pipeline.println(static_cast<double>(TCRTVal));

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}