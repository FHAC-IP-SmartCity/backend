#include "ESPNow/Master.h"

ESPNowMaster::ESPNowMaster(const uint8_t *slaveMac, int rfidSdaPin, int rfidSclPin)
    : device(slaveMac), rfidReader(rfidSdaPin, rfidSclPin) {}

void ESPNowMaster::init()
{
    rfidReader.init();
    device.init(onReceive);
    pipeline.println("Master: Initialisiert.");
}

void ESPNowMaster::loop()
{
    std::string cardData;

    if (rfidReader.readCard(1)) // RFID-Karte erkannt
    {
        pipeline.println("Master: RFID-Daten gelesen.");
        cardData = (char *)rfidReader.getBuffer(); // RFID-Daten abrufen
        pipeline.println(("Gelesene Daten: " + cardData).c_str());

        if (device.send(cardData)) // Daten senden
        {
            pipeline.println("Master: Daten erfolgreich gesendet.");
        }
        else
        {
            pipeline.println("Master: Fehler beim Senden der Daten.");
        }
    }
    delay(3000);
}

void ESPNowMaster::onReceive(const uint8_t *mac, const uint8_t *data, int len)
{
    pipeline.println("Master: Daten empfangen.");
    pipeline.println(("Empfangene Daten: " + std::string((char *)data, len)).c_str());
}
