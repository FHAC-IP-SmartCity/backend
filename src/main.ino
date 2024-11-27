#include <Arduino.h>
#include "BusLogic/CardRead.h"
#include "pipeline.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <BH1750.h>

void setup()
{
  Serial.begin(115200);
  pipeline.open();
  setupRFIDRead();
}

void loop()
{
  if (!pipeline.isOpen())
  {
    pipeline.open();
  }
  readDataFromCard();
  delay(3000);
}