#include <Arduino.h>

#include "Sensors/PhotoResistor.h"
#include "pipeline.h"
PhotoResistor photoResistor;
// #include "MACReader.h"

float photoValue = 0;

void setup()
{
    pipeline.open();
    photoResistor.init();
    // macReader.MACinit();
}

void loop()
{
    // Daten aus dem Buffer holen
    // Daten an den Server senden, wenn Daten vorhanden sind

    photoResistor.read();
    photoValue = photoResistor.getLux();
    pipeline.println(static_cast<int64_t>(photoValue));

    // macReader.readMACAddress();

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}