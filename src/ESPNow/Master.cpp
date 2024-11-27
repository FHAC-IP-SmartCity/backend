#include <Arduino.h>
#include "ESPNow/ESPNowDevice.h"
#include "BusLogic/RFIDReader.h"

// MAC-Adresse des Slaves
uint8_t slaveMac[] = {0xA0, 0xB7, 0x65, 0x2D, 0x78, 0x3C};

RFIDReader rfidReader(21, 22);
ESPNowDevice master(slaveMac);

void onReceive(const uint8_t *mac, const uint8_t *data, int len)
{
    Serial.print("Quittung empfangen: ");
    Serial.println((char *)data);
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
        Serial.println("RFID-Daten gelesen: " + String(cardData.c_str()));
        if (master.send(cardData))
        {
            Serial.println("Daten erfolgreich gesendet.");
        }
        else
        {
            Serial.println("Fehler beim Senden.");
        }
    }
    delay(3000);
}
