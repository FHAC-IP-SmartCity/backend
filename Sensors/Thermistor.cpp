#include "Thermistor.h"

void setupThermistor() {
  pinMode(THERMISTOR_PIN, INPUT);
  pinMode(RED_PIN_TH, OUTPUT);
  pinMode(BLUE_PIN_TH, OUTPUT);
  pinMode(GREEN_PIN_TH, OUTPUT);
}

void thermistorLogic() {
  int adcValue = analogRead(THERMISTOR_PIN);  // ADC-Wert lesen
  float voltage = (adcValue * SUPPLY_VOLTAGE) / ADC_MAX_VALUE;  // Spannung berechnen

  // Verhindern, dass eine Division durch 0 passiert
  if (voltage == 0) {
    Serial.println("Fehler: Spannung = 0");
    return;
  }

  float resistance = SERIES_RESISTOR * (SUPPLY_VOLTAGE / voltage - 1);  // Widerstand berechnen

  // Temperatur in Kelvin berechnen
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;  // (R/Ro)
  steinhart = log(steinhart);  // ln(R/Ro)
  steinhart /= B_COEFFICIENT;  // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);  // + (1/To)
  steinhart = 1.0 / steinhart;  // Invertieren
  float temperatureCelsius = steinhart - 273.15;  // In Celsius umrechnen

  // Ausgabe der Temperatur
  Serial.print("Temperatur: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");


  // Farbtemperatur berechnen
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  if (temperatureCelsius < 20) {
    blueValue = 255;
  } else if (temperatureCelsius < 30) {
    blueValue = map(temperatureCelsius, 20, 30, 255, 0);
    greenValue = map(temperatureCelsius, 20, 30, 0, 255);
  } else {
    greenValue = 255;
  }

  // RGB-LED ansteuern
  analogWrite(RED_PIN_TH, redValue);
  analogWrite(GREEN_PIN_TH, greenValue);
  analogWrite(BLUE_PIN_TH, blueValue);
  delay(1000);
}
