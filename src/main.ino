#ifndef RFIDWRITE_H
#define RFIDWRITE_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDWrite
{
<<<<<<< HEAD
  pipeline.open();
  setupRFIDRead();
=======
private:
    MFRC522 rfid;
    int ssPin;
    int rstPin;
>>>>>>> 53527ad0972c9167e4b61e117487a664f8b2545f

public:
    RFIDWrite(int ssPin, int rstPin);
    void begin();
    bool writeCard(const std::string &data);
};

#endif // RFIDWRITE_H
