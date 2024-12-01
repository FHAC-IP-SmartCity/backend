#include <Arduino.h>

#include "Sensors/Thermistor.h"
#include "pipeline.h"
Thermistor thermistor;

float therValue = 0;

void setup()
{
    pipeline.open();
    thermistor.init();
}

void loop()
{
    // Daten aus dem Buffer holen
    // Daten an den Server senden, wenn Daten vorhanden sind
    thermistor.read();
    therValue = thermistor.getTemperature();
    pipeline.println(static_cast<double>(therValue));

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}