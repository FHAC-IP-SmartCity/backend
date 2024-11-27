#include "Sensors/PhotoResistor.h"

void PhotoResistor::setup()
{
  pinMode(photoResistorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.println("PhotoResistor setup completed.");
}

void PhotoResistor::readData(SensorData &data)
{
  int lightLevel = analogRead(photoResistorPin);
  data.lux = lightLevel; // Update the global SensorData

  Serial.print("Light level: ");
  Serial.println(lightLevel);

  // Logic to handle light threshold
  if (lightLevel < lightThreshold)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    Serial.println("Light level below threshold, RED LED ON.");
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);
    Serial.println("Light level above threshold, BLUE and GREEN LEDs ON.");
  }
}
