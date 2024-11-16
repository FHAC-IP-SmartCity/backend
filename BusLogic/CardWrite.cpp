#include "CardWrite.h"

void setupRFIDWrite() {
    SPI.begin(18, 19, 23, 21);  // ESP32 SPI-Pins
    rfid.PCD_Init();
    Serial.println("RFID initialized. Place a card to write.");
}

void writeDataToCard(const char* data) {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        return;
    }
    
    byte sector = 1; // Sector to write to
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF; // Default key for authentication
    
    rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, sector * 4, &key, &(rfid.uid));

    byte buffer[16];
    memset(buffer, 0, sizeof(buffer));
    strncpy((char *)buffer, data, 16);

    MFRC522::StatusCode status = rfid.MIFARE_Write(sector * 4, buffer, 16);
    if (status == MFRC522::STATUS_OK) {
        Serial.println("Data written successfully.");
    } else {
        Serial.print("Writing failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}

