#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

// Pinbelegung
const int sensorPin = 32;   // TCRT5000-Sensorpin
const int redLEDPin = 25;   // Rote LED
const int greenLEDPin = 26; // Grüne LED
const int dunkelLED = 27;   // Dunkel LED

BH1750 lightMeter;

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        Serial.println("BH1750 ready");
    }
    else
    {
        Serial.println("BH1750 not detected. Check wiring!");
        while (1)
            ;
    }
    // Initialisierung der Pins
    pinMode(sensorPin, INPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);

    // LEDs starten im "frei" Zustand
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
}

void loop()
{
    int sensorValue = analogRead(sensorPin); // Lesen des analogen Werts vom TCRT5000

    // Ausgabe des Sensorwerts
    Serial.print("Sensorwert: ");
    Serial.println(sensorValue);

    // Logik für die LED-Steuerung
    if (sensorValue < 300)
    {                                   // Schwellenwert anpassen je nach Sensor
        digitalWrite(redLEDPin, HIGH);  // Rote LED an
        digitalWrite(greenLEDPin, LOW); // Grüne LED aus
        Serial.println("Parkplatz besetzt");
    }
    else
    {
        digitalWrite(redLEDPin, LOW);    // Rote LED aus
        digitalWrite(greenLEDPin, HIGH); // Grüne LED an
        Serial.println("Parkplatz frei");
    }

    float lux = lightMeter.readLightLevel(); // Lux-Wert vom BH1750 lesen

    // Lux-Wert und LED-Zustand auf dem pipeline Monitor anzeigen
    Serial.print("Lichtintensität: ");
    Serial.print(lux);
    Serial.println(" lx");

    if (lux > 700)
    {
        // Sehr hell → LEDs aus

        Serial.println("Zustand: LEDs aus");
        digitalWrite(dunkelLED, LOW);
    }
    else
    {
        // Dunkel → LEDs auf voller Intensität

        Serial.println("Zustand: LEDs voll");
        digitalWrite(dunkelLED, HIGH);
    }

    delay(500); // Kurze Pause
}

// Verkabelung:
// TCRT5000-Sensor:
// - VCC: 3.3V
// - GND: Masse
// - OUT: Sensorpin (32 im Code)
// LEDs:
// - Rote LED: Pin 25
// - Grüne LED: Pin 26
// Jede LED sollte mit einem Widerstand von 220 Ohm an Masse angeschlossen werden.