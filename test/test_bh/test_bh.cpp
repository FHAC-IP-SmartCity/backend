#include <Arduino.h>

#include "Sensors/BH1750Sensor.h"
#include "pipeline.h"

BH1750Sensor BH;
float lux = 0;

void setup()
{
    pipeline.open();
    BH.init();
}

void loop()
{
    BH.read();

    // Daten aus dem Buffer holen
    lux = BH.getLux();

    // Daten an den Server senden, wenn Daten vorhanden sind
    // Casting notwendig, da in pipeline nur double Werte erlaubt sind
    pipeline.println(static_cast<double>(lux));

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}