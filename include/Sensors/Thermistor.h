#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>
#include "pipeline.h"

class Thermistor
{
private:
    const uint8_t thermistorPin = 35;
    const float seriesResistor = 10000.0;    // Widerstandswert in Ohm (10kΩ)
    const float nominalTemperature = 25.0;   // Referenztemperatur (25°C)
    const float nominalResistance = 10000.0; // Nennwiderstand bei Referenztemperatur (10kΩ)
    const float bCoefficient = 3950.0;       // B-Koeffizient des Thermistors
    const float adcMaxValue = 4095.0;        // Maximaler ADC-Wert für 12-Bit-Auflösung
    const float supplyVoltage = 3.3;         // Versorgungsspannung

public:
    void init();
    void readData();
};

#endif
