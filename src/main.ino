#include <Arduino.h>
#include "MFRC522.h"
#include "SPI.h"
#include "Sensors/TCRT5000Sensor.h"

#define SS_PIN 5
#define RST_PIN 17
#define PIR 27

int counter = 0;

TCRT5000Sensor fstTrainWest;
TCRT5000Sensor sndTrainWest;

int fstTrainNum = 0;
int sndTrainNum = 0;

MFRC522 rfidBus(SS_PIN, RST_PIN);

const byte authorizedIDs[][7] = {
    {0x4, 0xAD, 0xA1, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0xC9, 0xA7, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0xA6, 0xB2, 0xA5, 0x6E, 0x26, 0x81},
};

const int numIDs = 3;

bool compareIDs(const byte *id1, const byte *id2, byte length)
{
    for (byte i = 0; i < length; i++)
    {
        if (id1[i] != id2[i])
        {
            return false;
        }
    }
    return true;
}

void setup()
{
    SPI.begin();
    rfidBus.PCD_Init();
    Serial.println("Scan PICC to see UID, SAK, type, and data blocks...");

    pinMode(13, OUTPUT);
    pinMode(PIR, INPUT);

    fstTrainWest.init(12);
    sndTrainWest.init(14);
}

void loop()
{
    if (rfidBus.PICC_IsNewCardPresent() && rfidBus.PICC_ReadCardSerial())
    {

        digitalWrite(13, HIGH);

        byte readID[7] = {0};
        for (byte i = 0; i < rfidBus.uid.size && i < 7; i++)
        {
            readID[i] = rfidBus.uid.uidByte[i];
        }

        Serial.print("Gelesene Karte: ");
        for (byte i = 0; i < 7; i++)
        {
            Serial.print(readID[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        // Überprüfen, ob die Karte autorisiert ist
        for (int i = 0; i < numIDs; i++)
        {
            if (compareIDs(readID, authorizedIDs[i], 7))
            {
                Serial.println("Karte autorisiert!");
                rfidBus.PICC_HaltA();
                rfidBus.PCD_StopCrypto1();
                return;
            }
        }

        Serial.println("Karte nicht autorisiert.");
        rfidBus.PICC_HaltA();
        rfidBus.PCD_StopCrypto1();
    }

    if (digitalRead(PIR) == HIGH)
    {
        Serial.println("Bewegung erkannt!");
        counter++;
    }

    fstTrainWest.read();
    sndTrainWest.read();

    int fstTrainNum = fstTrainWest.getTCRTValue();
    int sndTrainNum = sndTrainWest.getTCRTValue();

    if (fstTrainNum > 2000 && sndTrainNum > 2000)
    {
        Serial.println("Train in station!");
    }
    else if (fstTrainNum > 2000)
    {
        Serial.println("train is comming!");
    }

    digitalWrite(13, LOW);
    delay(100);
}
