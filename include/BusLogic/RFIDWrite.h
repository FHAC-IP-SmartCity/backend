#ifndef RFIDWRITE_H
#define RFIDWRITE_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDWrite
{
private:
    MFRC522 rfid;
    int ssPin;
    int rstPin;

public:
    RFIDWrite(int ssPin, int rstPin);
    void begin();
    bool writeCard(const std::string &data);
};

#endif // RFIDWRITE_H
