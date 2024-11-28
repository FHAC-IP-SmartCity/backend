#include "Sensors/Thermistor.h"

void Thermistor::setup()
{
  pinMode(thermistorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pipeline.println("Thermistor setup completed.");
}

void Thermistor::readData(SensorData &data)
{
  int adcValue = analogRead(thermistorPin);
  float resistance = seriesResistor * ((adcMaxValue / (float)adcValue) - 1.0);
  float steinhart;
  steinhart = resistance / nominalResistance;       // R/R0
  steinhart = log(steinhart);                       // ln(R/R0)
  steinhart /= bCoefficient;                        // 1/B * ln(R/R0)
  steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/T0)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // Convert to Celsius

  data.temperature = steinhart; // Update the global SensorData
  pipeline.println("Thermistor temperature: ");
  pipeline.println(String(steinhart).c_str());
  pipeline.println(" °C");
}
