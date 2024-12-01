#include <Arduino.h>

#include "Sensors/PhotoResistor.h"
#include "pipeline.h"

PhotoResistor photoResistor;
float photoValue = 0;

void setup()
{
    pipeline.open();
    photoResistor.init();
}

void loop()
{
    // Daten aus dem Buffer holen
    photoResistor.read();
    photoValue = photoResistor.getLux();
    pipeline.println(static_cast<int64_t>(photoValue));

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}