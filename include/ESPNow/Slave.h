#ifndef ESPNOW_SLAVE_H
#define ESPNOW_SLAVE_H

#include <string>
#include "ESPNow/ESPNowDevice.h"
#include "pipeline.h"

class ESPNowSlave
{
private:
    ESPNowDevice device;
    static ESPNowSlave *instance; // Zeiger auf die aktuelle Instanz

    // Statische Callback-Funktion
    static void onReceiveStatic(const uint8_t *mac, const uint8_t *data, int len);

    // Nicht-statische Methode für die eigentliche Verarbeitung
    void onReceive(const uint8_t *mac, const uint8_t *data, int len);

public:
    ESPNowSlave(const uint8_t *masterMac);
    void init();
    void loop();
};

#endif
