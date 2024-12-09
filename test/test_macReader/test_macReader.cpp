#include <Arduino.h>

#include "MACReader.h"
#include "pipeline.h"

MACReader macReader;

void setup()
{
    pipeline.open();
    macReader.init();
}

void loop()
{
    macReader.read();
    delay(1000);
}