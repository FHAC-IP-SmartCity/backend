#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>
#include "pipeline.h"

class Thermistor
{
private:
    uint8_t pin;
    const float seriesResistor = 10000.0;    // Widerstandswert in Ohm (10kΩ)
    const float nominalTemperature = 25.0;   // Referenztemperatur (25°C)
    const float nominalResistance = 10000.0; // Nennwiderstand bei Referenztemperatur (10kΩ)
    const float bCoefficient = 3950.0;       // B-Koeffizient des Thermistors
    const float adcMaxValue = 4095.0;        // Maximaler ADC-Wert für 12-Bit-Auflösung
    const float supplyVoltage = 3.3;         // Versorgungsspannung
    float steinhart;

public:
    void init(uint8_t pin = 35);
    void read();
    float getTemperature() { return steinhart; }
};

#endif
