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
    MFRC522::MIFARE_Key defaultKey;

    byte buffer[18];

    // Hilfsmethode für Authentifizierung
    bool authenticate(uint8_t sector);

    // Hilfsmethode für das Lesen von Daten
    void logError(const String &msg)
    {
        pipeline.send(1000, msg.c_str(), msg.length());
    }

public:
    RFIDReader(uint8_t ssPin, uint8_t rstPin);
    void init();
    bool isCardPresent();
    bool readCard(uint8_t sector = 1);
    bool writeCard(const std::string &data, uint8_t sector = 1);
    byte *getBuffer();
};

#endif
