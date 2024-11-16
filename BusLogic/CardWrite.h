#ifndef CARDWRITE_H
#define CARDWRITE_H

#include <SPI.h>
#include <MFRC522.h>
    
extern MFRC522 rfid;
void setupRFIDWrite();
void writeDataToCard(const char* data);

#endif // CARDWRITE_H