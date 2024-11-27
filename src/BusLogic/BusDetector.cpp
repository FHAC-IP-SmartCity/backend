#include "BusLogic/BusDetector.h"
#include "pipeline.h"

// Define the RFID instance
extern MFRC522 rfid;

void setupRFID()
{
    // Initialize SPI bus
    SPI.begin(18, 19, 23, 21); // ESP32 SPI-Pins
    rfid.PCD_Init();
    Serial.println("RFID reader initialized.");
    if (rfid.PCD_PerformSelfTest())
    {
        Serial.println("RFID self-test passed.");
    }
    else
    {
        Serial.println("RFID self-test failed.");
    }
}

void setupBusDetector()
{
    setupRFID();
    rfid.PCD_DumpVersionToSerial(); // Output details of the RFID reader
    Serial.println(F("Scan a card or tag to see the UID and data blocks..."));
}

void busDetector()
{
    Serial.println("Checking for new cards...");

    // Look for new cards
    if (!rfid.PICC_IsNewCardPresent())
    {
        Serial.println("No new card detected.");
        return;
    }

    // Select one of the cards
    if (!rfid.PICC_ReadCardSerial())
    {
        Serial.println("Failed to read card serial.");
        return;
    }

    // A card has been detected, print the UID
    Serial.print("Card UID: ");
    for (byte i = 0; i < rfid.uid.size; i++)
    {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Print card type
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    Serial.print("PICC Type: ");
    Serial.println(rfid.PICC_GetTypeName(piccType));

    // Dump the data of the card
    rfid.PICC_DumpToSerial(&(rfid.uid));

    // Halt PICC to stop reading it continuously
    rfid.PICC_HaltA();
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
}
