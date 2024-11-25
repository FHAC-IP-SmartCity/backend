#include <Wire.h>
#include <BH1750.h>

#define PIR_PIN 34      // Pin für den HC-SR505 PIR-Sensor
// HC-SR505 (PIR-Sensor)
// VCC an 3.3V 
// OUT an einen GPIO 34.
// GND an GND 


#define MIC_PIN 35      // ADC-Pin für den GY-MAX9814 Mikrofonverstärker
// GY-MAX9814 (Mikrofonverstärker)
// VCC an 3.3V 
// OUT an GPIO 35 
// GND an GND 


// BH1750 (Lichtsensor)
// VCC an 3.3V 
// GND an GND 
// SDA an GPIO 21.
// SCL an GPIO 22.


BH1750 lightMeter;      // Objekt für den BH1750 Lichtsensor

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("\nI2C-Scanner gestartet");

  // I2C-Scanner
  byte error, address;
  int devicesFound = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C-Gerät gefunden bei Adresse 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      devicesFound++;
    }
  }

  if (devicesFound == 0) {
    Serial.println("Keine I2C-Geräte gefunden");
  } else {
    Serial.println("I2C-Scan abgeschlossen");
  }

  // Initialisierung des PIR-Sensors
  pinMode(PIR_PIN, INPUT);

  // Initialisierung des Lichtsensors
  if (lightMeter.begin()) {
    Serial.println("BH1750 Lichtsensor initialisiert.");
  } else {
    Serial.println("Fehler beim Initialisieren des BH1750.");
  }
}

void loop() {
  // PIR-Sensor auslesen
  int pirState = digitalRead(PIR_PIN);
  if (pirState == HIGH) {
    Serial.println("Bewegung erkannt!");
  } else {
    Serial.println("Keine Bewegung.");
  }

  // Mikrofonverstärker auslesen
  int micValue = analogRead(MIC_PIN);
  Serial.print("Mikrofonwert: ");
  Serial.println(micValue);

  // Lichtsensor auslesen
  float lux = lightMeter.readLightLevel();
  if (lux == -1) {
    Serial.println("Fehler beim Auslesen des BH1750.");
  } else {
    Serial.print("Lichtstärke: ");
    Serial.print(lux);
    Serial.println(" lx");
  }

  // Kurze Verzögerung
  delay(1000);
}

