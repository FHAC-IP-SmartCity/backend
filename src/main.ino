#include <Arduino.h>
#include "MFRC522.h"
#include "SPI.h"

#include "Sensors/TCRT5000.h"

#define SS_PIN 5
#define RST_PIN 17
#define PIR 27

int counter = 0;
bool motionDetected = false;

MFRC522 rfidBus(SS_PIN, RST_PIN);

TCRT fstTrainWest;
TCRT sndTrainWest;

int fstTrainNum = 0;
int sndTrainNum = 0;

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
    pipeline.open();
    pipeline.println("Scan PICC to see UID.");

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

        // Check if the scanned ID is in the authorized IDs
        for (int i = 0; i < numIDs; i++)
        {
            if (compareIDs(readID, authorizedIDs[i], 7))
            {
                pipeline.println("Bus is on bus stop.");
                pipeline.send(3110, static_cast<int64_t>(1));

                rfidBus.PICC_HaltA();
                rfidBus.PCD_StopCrypto1();
                return;
            }
        }

        pipeline.println("Not a bus.");
        pipeline.send(3110, static_cast<int64_t>(0));

        rfidBus.PICC_HaltA();
        rfidBus.PCD_StopCrypto1();
    }

    if (digitalRead(PIR) == HIGH)
    {
        if (!motionDetected)
        {
            pipeline.println("Motion detected.");
            counter++;
            motionDetected = true;

            pipeline.println(static_cast<int64_t>(counter));
            pipeline.send(3110, static_cast<int64_t>(counter));
        }
    }
    else
    {
        motionDetected = false;
    }

    fstTrainWest.read();
    sndTrainWest.read();

    int fstTrainNum = fstTrainWest.getTCRTValue();
    int sndTrainNum = sndTrainWest.getTCRTValue();

    pipeline.println(static_cast<int64_t>(fstTrainNum));
    pipeline.println(static_cast<int64_t>(sndTrainNum));

    if (fstTrainNum > 2000 && sndTrainNum > 2000)
    {
        pipeline.println(static_cast<int64_t>(fstTrainNum));
        pipeline.println(static_cast<int64_t>(sndTrainNum));
        pipeline.send(3210, static_cast<int64_t>(1));
        pipeline.send(3220, static_cast<int64_t>(1));
    }
    else if (fstTrainNum > 2000)
    {
        pipeline.println(static_cast<int64_t>(fstTrainNum));
        pipeline.send(3210, static_cast<int64_t>(1));
        pipeline.send(3220, static_cast<int64_t>(0));
    }
    else
    {
        pipeline.send(3210, static_cast<int64_t>(0));
        pipeline.send(3220, static_cast<int64_t>(0));
    }

    digitalWrite(13, LOW);
    delay(1000);
}
