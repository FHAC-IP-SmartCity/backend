#include "BusLogic/RFIDWrite.h"
#include "pipeline.h"

RFIDWrite::RFIDWrite(int ssPin, int rstPin) : rfid(ssPin, rstPin), ssPin(ssPin), rstPin(rstPin) {}

void RFIDWrite::begin()
{
    SPI.begin();
    rfid.PCD_Init();
    pipeline.println("RFID initialized.");
}

bool RFIDWrite::writeCard(const std::string &data)
{
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {
        return false;
    }

    byte sector = 1; // Sector to write to
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++)
        key.keyByte[i] = 0xFF; // Default key for authentication

    if (rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, sector * 4, &key, &(rfid.uid)) != MFRC522::STATUS_OK)
    {
        pipeline.println("Authentication failed.");
        return false;
    }

    byte buffer[16];
    memset(buffer, 0, sizeof(buffer));
    strncpy((char *)buffer, data.c_str(), 16);

    if (rfid.MIFARE_Write(sector * 4, buffer, 16) != MFRC522::STATUS_OK)
    {
        pipeline.println("Write failed.");
        return false;
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return true;
}
