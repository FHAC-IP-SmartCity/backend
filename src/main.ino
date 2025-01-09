#include <Arduino.h>
#include "MFRC522.h"
#include "SPI.h"

#define SS_PIN 5
#define RST_PIN 17

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Scan PICC to see UID, SAK, type, and data blocks...");
}

void loop()
{
}
