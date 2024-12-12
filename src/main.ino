#include <Arduino.h>

#include "BusLogic/RFIDReader.h"
#include "pipeline.h"

RFIDReader RFID(5, 22);
const int ledPin = 13;
std::string data;

void setup()
{
    // pipeline.open();
    RFID.init();
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    // RFID-Reader auslesen
    RFID.readCard();

    // Daten aus dem Buffer holen
    data = std::string((char *)RFID.getBuffer());

    // Daten an den Server senden, wenn Daten vorhanden sind
    if (data.empty())
    {
        return;
    }
    else
    {
        Serial.println(data.c_str());
        digitalWrite(ledPin, HIGH);
        delay(1000);
    }

    // Buffer leeren, nach einmaliger Ausgabe
    memset(RFID.getBuffer(), 0, sizeof(RFID.getBuffer()));
    delay(2000);
    digitalWrite(ledPin, LOW);
}