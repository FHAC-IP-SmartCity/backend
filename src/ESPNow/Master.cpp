#include <Arduino.h>
#include "ESPNow/ESPNowDevice.h"
#include "BusLogic/RFIDReader.h"
#include "pipeline.h"
#include <string.h>

// MAC-Adresse des Slaves
uint8_t slaveMac[] = {0xA0, 0xB7, 0x65, 0x2D, 0x78, 0x3C};

RFIDReader rfidReader(21, 22);
ESPNowDevice master(slaveMac);

void onReceive(const uint8_t *mac, const uint8_t *data, int len)
{
    pipeline.println("Quittung empfangen: ");
    pipeline.println((char *)data);
}

void setup()
{
    Serial.begin(115200);
    rfidReader.begin();
    master.begin(onReceive);
}

void loop()
{
    std::string cardData;
    if (rfidReader.readCard(cardData))
    {
        pipeline.println(strcat("RFID-Daten gelesen: ", cardData.c_str()));

        if (master.send(cardData))
        {
            pipeline.println("Daten erfolgreich gesendet.");
        }
        else
        {
            pipeline.println("Fehler beim Senden.");
        }
    }
    delay(3000);
}
