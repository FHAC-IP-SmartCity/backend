#include "BusLogic/RFIDReader.h"

RFIDReader::RFIDReader(uint8_t ssPin, uint8_t rstPin) : ssPin(ssPin), rstPin(rstPin), rfid(ssPin, rstPin)
{
    // Standard-Schlüssel initialisieren
    for (uint8_t i = 0; i < 6; i++)
        defaultKey.keyByte[i] = 0xFF;
}

void RFIDReader::init()
{
    SPI.begin(); // SPI initialisieren
    rfid.PCD_Init();
    Serial.println("RFID-Reader initialisiert.");
}

bool RFIDReader::isCardPresent()
{
    return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

bool RFIDReader::authenticate(uint8_t sector)
{
    MFRC522::StatusCode status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, sector * 4, &defaultKey, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    {
        logError(String(rfid.GetStatusCodeName(status)));
        return false;
    }
    return true;
}

bool RFIDReader::readCard(std::string &data, uint8_t sector)
{
    if (!isCardPresent())
        return false;

    if (!authenticate(sector))
        return false;

    byte buffer[18];
    byte size = sizeof(buffer);
    MFRC522::StatusCode status = rfid.MIFARE_Read(sector * 4, buffer, &size);
    if (status != MFRC522::STATUS_OK)
    {
        logError("Lesen fehlgeschlagen: " + String(rfid.GetStatusCodeName(status)));
        return false;
    }

    data.assign((char *)buffer, size);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return true;
}

bool RFIDReader::writeCard(const std::string &data, uint8_t sector)
{
    if (!isCardPresent())
        return false;

    if (!authenticate(sector))
        return false;

    byte buffer[16];
    memset(buffer, 0, sizeof(buffer));
    strncpy((char *)buffer, data.c_str(), sizeof(buffer));

    MFRC522::StatusCode status = rfid.MIFARE_Write(sector * 4, buffer, 16);
    if (status != MFRC522::STATUS_OK)
    {
        logError("Schreiben fehlgeschlagen: " + String(rfid.GetStatusCodeName(status)));
        return false;
    }

    Serial.println("Daten erfolgreich geschrieben.");
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return true;
}
