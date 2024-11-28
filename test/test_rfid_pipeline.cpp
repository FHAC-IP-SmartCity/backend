#include <Arduino.h>
#include "BusLogic/RFIDReader.h"
#include "pipeline.h"

// Dummy RFID and pipeline objects to emulate behavior in the test
MFRC522 rfid;
// TODO: Replace with actual RFIDReader pins
RFIDReader rfidReader(21, 22);

void init()
{
    pipeline.init();
    rfid.PCD_Init();
}

void loop()
{
    pipeline.println("Starting test...");

    // Teste, ob eine Karte vorhanden ist
    if (!rfidReader.isCardPresent())
    {
        pipeline.println("No card present.");
        delay(2000);
        return;
    }

    // Lese die Karte
    if (!rfidReader.readCard())
    {
        pipeline.println("Failed to read card.");
        delay(2000);
        return;
    }

    // Gebe die gelesenen Daten aus
    byte *buffer = rfidReader.getBuffer();
    for (int i = 0; i < 18; i++)
    {
        pipeline.println(String(buffer[i], HEX).c_str());
        pipeline.println("");
    }
    pipeline.println("");

    // Füge eine kleine Verzögerung ein, um den Loop-Output lesbar zu halten
    delay(2000);
}
