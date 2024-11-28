#ifndef BUSDETECTOR_H
#define BUSDETECTOR_H

#include <SPI.h>
#include <MFRC522.h>
#include "pipeline.h"

// Define the pins for the RFID reader
#define SS_PIN 21  // SDA pin
#define RST_PIN 22 // RST pin

// Declare the RFID instance as extern
extern MFRC522 rfid;

void setupRFID();
void setupBusDetector();
void busDetector();

#endif // BUSDETECTOR_H
