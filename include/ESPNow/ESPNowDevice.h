#ifndef ESPNOWDEVICE_H
#define ESPNOWDEVICE_H

#include <esp_now.h>
#include <WiFi.h>
#include <functional>
#include "pipeline.h"

class ESPNowDevice
{
private:
    uint8_t peerMac[6];
    std::function<void(const uint8_t *, const uint8_t *, int)> onReceiveCallback;

    static void onReceiveStatic(const uint8_t *mac, const uint8_t *data, int len);

public:
    ESPNowDevice(const uint8_t *macAddress);
    void begin(std::function<void(const uint8_t *, const uint8_t *, int)> callback);
    bool send(const std::string &message);
};

#endif // ESPNOWDEVICE_H
