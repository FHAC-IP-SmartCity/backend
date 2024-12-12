#include <Arduino.h>

// Pinbelegung
const int buttonPin = 26; // Button
const int LED = 27;       // LED

void setup()
{
    Serial.begin(115200);

    // Initialisierung der Pins
    pinMode(buttonPin, INPUT_PULLUP); // Pull-up-Widerstand aktivieren
    pinMode(LED, OUTPUT);

    // LEDs starten im "frei" Zustand
    digitalWrite(LED, LOW);
}

void loop()
{
    // Lesen des digitalen Werts vom Button (invertierte Logik wegen Pull-up)
    int buttonState = digitalRead(buttonPin);

    // Logik für die LED-Steuerung
    if (buttonState == HIGH) // Button gedrückt
    {
        digitalWrite(LED, HIGH); // LED an
        Serial.println("Button gedrückt: LED an");
    }
    else // Button nicht gedrückt
    {
        digitalWrite(LED, LOW); // LED aus
        Serial.println("Button losgelassen: LED aus");
    }

    delay(50); // Entprellung (Debounce)
}
