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

    // callback function to be called when a message is received
    std::function<void(const uint8_t *, const uint8_t *, int)> onReceiveCallback;

    // static callback function to be called when a message is received
    static void onReceiveStatic(const uint8_t *mac, const uint8_t *data, int len);

public:
    ESPNowDevice(const uint8_t *macAddress);
    void init(std::function<void(const uint8_t *, const uint8_t *, int)> callback);

    // send a message to the peer device
    bool send(const std::string &message);
};

#endif
