#ifndef THERMISTOR_H
#include <Arduino.h>

#define THERMISTOR_PIN 35
#define RED_PIN_TH 14
#define BLUE_PIN_TH 12
#define GREEN_PIN_TH 13
#define SERIES_RESISTOR 10000  // Widerstandswert in Ohm (10kΩ)
#define NOMINAL_TEMPERATURE 25  // Referenztemperatur (25°C)
#define NOMINAL_RESISTANCE 10000  // Nennwiderstand des Thermistors bei Referenztemperatur (10kΩ)
#define B_COEFFICIENT 3950  // B-Koeffizient des Thermistors
#define ADC_MAX_VALUE 4095  // Maximaler ADC-Wert für 12-Bit-Auflösung
#define SUPPLY_VOLTAGE 3.3  // Versorgungsspannung



void setupThermistor();
void thermistorLogic();

#endif