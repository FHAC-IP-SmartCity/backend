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

void BH1750Sensor::read(SensorData &data)
{
    float lux = lightMeter.readLightLevel();
    if (lux == -1)
    {
        pipeline.println("Fehler beim Auslesen des BH1750.");
        data.lux = -1; // Fehlerwert
    }
    else
    {
        data.lux = lux;
    }
}
