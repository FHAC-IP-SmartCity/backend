#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// Erstellen Sie ein BME680-Objekt
Adafruit_BME680 bme; 

#define SENSOR_ADDRESS 0x77  // BME680 I2C-Adresse (Standard ist 0x77, kann aber auf 0x76 geändert werden)

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // GPIO21 für SDA, GPIO22 für SCL beim ESP32

  // I2C-Scanner zum Ermitteln der Adresse
  Serial.println("I2C-Scanner wird gestartet...");
  bool sensorFound = false;
  
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Gerät gefunden bei Adresse 0x");
      Serial.println(address, HEX);
      sensorFound = true;
    }
  }

  if (!sensorFound) {
    Serial.println("Kein I2C-Gerät gefunden!");
  }

  // Initialisieren Sie den BME680-Sensor
  if (!bme.begin()) {
    Serial.println("Sensor konnte nicht initialisiert werden.");
    while (1);
  }

  Serial.println("BME680 Sensor erfolgreich initialisiert!");
}

void loop() {
  // Sensordaten anfordern
  if (bme.performReading()) {
    // Temperatur in Grad Celsius
    float temperature = bme.temperature;
    // Luftfeuchtigkeit in Prozent
    float humidity = bme.humidity;
    // Luftdruck in hPa
    float pressure = bme.pressure / 100.0;  // Umrechnung von Pa in hPa
    // Gassensor-Widerstand (VOC-Wert, niedrigere Werte bedeuten bessere Luftqualität)
    float gas = bme.gas_resistance / 1000.0;  // In KΩ

    // Ausgabe der Daten auf der seriellen Konsole
    Serial.print("Temperatur: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Luftfeuchtigkeit: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Luftdruck: ");
    Serial.print(pressure);
    Serial.println(" hPa");

    Serial.print("Gas-Widerstand (VOC): ");
    Serial.print(gas);
    Serial.println(" KΩ");

  } else {
    Serial.println("Fehler beim Auslesen der Sensorwerte.");
  }

  delay(1000);  // Eine Sekunde warten, bevor neue Daten ausgelesen werden
}
