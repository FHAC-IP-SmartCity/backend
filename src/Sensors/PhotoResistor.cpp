#include "Sensors/PhotoResistor.h"

void PhotoResistor::init(uint8_t pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);
  pipeline.println("PhotoResistor init completed.");
}

void PhotoResistor::readData()
{
  int lightLevel = analogRead(pin);
  lux = lightLevel; // Update the global SensorData

  pipeline.println("Light level: ");
  pipeline.println(lightLevel);

  // Logic to handle light threshold
  if (lightLevel < lightThreshold)
  {
    pipeline.println("Light level below threshold, RED LED ON.");
  }
  else
  {
    pipeline.println("Light level above threshold, BLUE and GREEN LEDs ON.");
  }
}
