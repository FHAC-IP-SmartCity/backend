#include "Sensors/Thermistor.h"

void Thermistor::init(uint8_t pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);
  pipeline.println("Thermistor init completed.");
}

void Thermistor::read()
{
  int adcValue = analogRead(pin);
  float resistance = seriesResistor * ((adcMaxValue / (float)adcValue) - 1.0);
  float steinhart;
  steinhart = resistance / nominalResistance;       // R/R0
  steinhart = log(steinhart);                       // ln(R/R0)
  steinhart /= bCoefficient;                        // 1/B * ln(R/R0)
  steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/T0)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // Convert to Celsius

  this->steinhart = steinhart;
}
