#include <Arduino.h>
#include "BusLogic/CardRead.h"
#include "pipeline.h"

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