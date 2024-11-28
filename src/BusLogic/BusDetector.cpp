#include "BusLogic/BusDetector.h"
#include "pipeline.h"

// Define the RFID instance
extern MFRC522 rfid;

void setupRFID()
{
    // Initialize SPI bus
    SPI.begin(18, 19, 23, 21); // ESP32 SPI-Pins
    rfid.PCD_Init();
    pipeline.println("RFID reader initialized.");
    if (rfid.PCD_PerformSelfTest())
    {
        pipeline.println("RFID self-test passed.");
    }
    else
    {
        pipeline.println("RFID self-test failed.");
    }
}

void setupBusDetector()
{
    setupRFID();
    rfid.PCD_DumpVersionToSerial(); // Output details of the RFID reader
    pipeline.println("Scan a card or tag to see the UID and data blocks...");
}

void busDetector()
{
    pipeline.println("Checking for new cards...");

    // Look for new cards
    if (!rfid.PICC_IsNewCardPresent())
    {
        pipeline.println("No new card detected.");
        return;
    }

    // Select one of the cards
    if (!rfid.PICC_ReadCardSerial())
    {
        pipeline.println("Failed to read card serial.");
        return;
    }

    // A card has been detected, print the UID
    pipeline.println("Card UID: ");
    for (byte i = 0; i < rfid.uid.size; i++)
    {
        pipeline.println(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        pipeline.println(String(rfid.uid.uidByte[i], HEX).c_str());
    }
    pipeline.println("");

    // Print card type
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    pipeline.println("PICC Type: ");
    // pipeline.println(rfid.PICC_GetTypeName(piccType).c_str());

    // Dump the data of the card
    rfid.PICC_DumpToSerial(&(rfid.uid));

    // Halt PICC to stop reading it continuously
    rfid.PICC_HaltA();
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
}
