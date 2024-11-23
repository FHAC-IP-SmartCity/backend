#ifndef CARDREAD_H
#define CARDREAD_H

#include <SPI.h>
#include <MFRC522.h>

extern MFRC522 rfid;
void setupRFIDRead();
void readDataFromCard();

#endif // CARDREAD_H