#include <Arduino.h>
#include "BusLogic/CardRead.h"
#include "pipeline.h"

// Dummy RFID and pipeline objects to emulate behavior in the test
MFRC522 rfid;
PipeLine pipeline;

void setup()
{
    Serial.begin(115200);
    pipeline.init(); // Initialisiere die Pipeline
    setupRFIDRead(); // Initialisiere RFID Reader
}

void loop()
{
    pipeline.println("Starting test...");

    // Lese Daten von der Karte
    readDataFromCard();

    // Füge eine kleine Verzögerung ein, um den Loop-Output lesbar zu halten
    delay(2000);
}
