#include "Sensors/PhotoResistor.h"

void PhotoResistor::setup()
{
  pinMode(photoResistorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pipeline.println("PhotoResistor setup completed.");
}

void PhotoResistor::readData(SensorData &data)
{
  int lightLevel = analogRead(photoResistorPin);
  data.lux = lightLevel; // Update the global SensorData

  pipeline.println("Light level: ");
  pipeline.println(String(lightLevel).c_str());

  // Logic to handle light threshold
  if (lightLevel < lightThreshold)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    pipeline.println("Light level below threshold, RED LED ON.");
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);
    pipeline.println("Light level above threshold, BLUE and GREEN LEDs ON.");
  }
}
