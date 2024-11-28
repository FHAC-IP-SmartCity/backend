#include "ESPNow/ESPNowDevice.h"
#include "pipeline.h"

// MAC-Adresse des Masters
uint8_t masterMac[] = {0xA0, 0xB7, 0x65, 0x2D, 0x5C, 0x2C};

ESPNowDevice slave(masterMac);

void onReceive(const uint8_t *mac, const uint8_t *data, int len)
{
    pipeline.println("Daten empfangen: ");
    pipeline.println((char *)data);

    // Quittung senden
    std::string acknowledgment = "Quittung erhalten";
    slave.send(acknowledgment);
}

void setup()
{
    Serial.begin(115200);
    slave.begin(onReceive);
}

void loop()
{
    delay(1000);
}
