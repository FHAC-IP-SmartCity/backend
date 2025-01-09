#include <Arduino.h>
#include "MFRC522.h"
#include "SPI.h"

#define SS_PIN 5
#define RST_PIN 17

MFRC522 rfid(SS_PIN, RST_PIN);

const byte authorizedIDs[][7] = {
    {0x4, 0xAD, 0xA1, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0xC9, 0xA7, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0xA6, 0xB2, 0xA5, 0x6E, 0x26, 0x81},
};

const int numIDs = 3;

bool compareIDs(const byte *id1, const byte *id2, byte length)
{
    for (byte i = 0; i < length; i++)
    {
        if (id1[i] != id2[i])
        {
            return false;
        }
    }
    return true;
}

void setup()
{
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("Scan PICC to see UID, SAK, type, and data blocks...");
}

void loop()
{
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
    {
        byte readID[7] = {0};
        for (byte i = 0; i < rfid.uid.size && i < 7; i++)
        {
            readID[i] = rfid.uid.uidByte[i];
        }

        Serial.print("Gelesene Karte: ");
        for (byte i = 0; i < 7; i++)
        {
            Serial.print(readID[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        // Überprüfen, ob die Karte autorisiert ist
        for (int i = 0; i < numIDs; i++)
        {
            if (compareIDs(readID, authorizedIDs[i], 7))
            {
                Serial.println("Karte autorisiert!");
                rfid.PICC_HaltA();
                rfid.PCD_StopCrypto1();
                return;
            }
        }

        Serial.println("Karte nicht autorisiert.");
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }
}
