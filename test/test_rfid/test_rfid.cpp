#include <Arduino.h>

#include "BusLogic/RFIDReader.h"
#include "pipeline.h"

RFIDReader RFID(21, 22);
std::string data;

void setup()
{
    pipeline.open();
    RFID.init();
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
        pipeline.println(data.c_str());
    }

    // Buffer leeren, nach einmaliger Ausgabe
    memset(RFID.getBuffer(), 0, sizeof(RFID.getBuffer()));
    delay(3000);
}