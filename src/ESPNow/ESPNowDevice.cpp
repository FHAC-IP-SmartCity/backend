#include "ESPNow/ESPNowDevice.h"

ESPNowDevice::ESPNowDevice(const uint8_t *macAddress)
{
    memcpy(peerMac, macAddress, 6);
}

void ESPNowDevice::init(std::function<void(const uint8_t *, const uint8_t *, int)> callback)
{
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK)
    {
        pipeline.println("ESP-NOW initialization failed!");
        return;
    }

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerMac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    while (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        delay(100); // Warten und erneut versuchen
        pipeline.println("Retrying to add peer...");
    }

    onReceiveCallback = callback;
    esp_now_register_recv_cb(onReceiveStatic);
}

bool ESPNowDevice::send(const std::string &message)
{
    esp_err_t result = esp_now_send(peerMac, (const uint8_t *)message.c_str(), message.length());
    return result == ESP_OK;
}

std::string ESPNowDevice::macToString(const uint8_t *mac)
{
    return std::string();
}
void ESPNowDevice::onReceiveStatic(const uint8_t *mac, const uint8_t *data, int len)
{
    // Dummy implementation to redirect to the user's callback
}
