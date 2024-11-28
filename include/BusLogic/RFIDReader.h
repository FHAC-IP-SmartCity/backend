#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>
#include "pipeline.h"

class RFIDReader
{
private:
    MFRC522 rfid;

    uint8_t ssPin;
    uint8_t rstPin;

    // Default-Key for Authentifizierung
    MFRC522::MIFARE_Key defaultKey;

    // Helper method to authenticate a sector
    bool authenticate(uint8_t sector);

    // Helper method to log errors
    void logError(const String &msg)
    {
        pipeline.send(1, msg.c_str(), msg.length());
    }

public:
    RFIDReader(uint8_t ssPin, uint8_t rstPin);
    void init();

    // Checks if a card is present
    bool isCardPresent();

    // Reads data from a card
    bool readCard(std::string &data, uint8_t sector = 1);

    // Writes data to a card
    bool writeCard(const std::string &data, uint8_t sector = 1);
};

#endif
