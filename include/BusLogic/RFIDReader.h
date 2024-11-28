#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDReader
{
private:
    MFRC522 rfid;
    int ssPin;
    int rstPin;

public:
    RFIDReader(int ssPin, int rstPin);
    void begin();
    bool readCard(std::string &data);
    bool writeCard(const std::string &data);
};

#endif // RFIDREADER_H
