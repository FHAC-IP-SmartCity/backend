#include "Sensors/BH1750Sensor.h"

void BH1750Sensor::init()
{
    if (lightMeter.begin())
    {
        pipeline.println("BH1750 Lichtsensor erfolgreich initialisiert.");
    }
    else
    {
        pipeline.println("Fehler beim Initialisieren des BH1750.");
    }
}

void BH1750Sensor::read()
{
    float lux = lightMeter.readLightLevel();
    if (lux == -1)
    {
        pipeline.println("Fehler beim Auslesen des BH1750.");
        }
    else
    {
        pipeline.println("Lichtstärke: ");
        pipeline.println(lux);
        pipeline.println(" lx");
    }
}
