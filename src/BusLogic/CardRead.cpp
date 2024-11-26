#include "BusLogic/CardRead.h"
#include "pipeline.h"

void setupRFIDRead()
{
    // Initialize SPI bus
    SPI.begin(18, 19, 23, 21); // ESP32 SPI-Pins
    rfid.PCD_Init();
}

void readDataFromCard()
{
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {
        return;
    }

    byte sector = 1; // Sector to read from
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++)
        key.keyByte[i] = 0xFF; // Default key for authentication

    rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, sector * 4, &key, &(rfid.uid));

    byte buffer[18];
    byte size = sizeof(buffer);
    MFRC522::StatusCode status = rfid.MIFARE_Read(sector * 4, buffer, &size);
    if (status == MFRC522::STATUS_OK)
    {
        std::string message = std::string((char *)buffer);
        pipeline.send(110, (char *)buffer, message.length());
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}
