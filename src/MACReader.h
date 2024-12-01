#include <WiFi.h>
#include <esp_wifi.h>
#include "pipeline.h"
#include <string>

class MACReader
{
public:
    void init()
    {
        WiFi.mode(WIFI_STA);
        pipeline.println("[DEFAULT] ESP32 Board MAC Address: ");
    }

    void read()
    {
        uint8_t baseMac[6];
        esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
        if (ret == ESP_OK)
        {
            char macStr[18];
            sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                    baseMac[0], baseMac[1], baseMac[2],
                    baseMac[3], baseMac[4], baseMac[5]);
            pipeline.println(macStr);
        }
        else
        {
            pipeline.println("Failed to read MAC address");
        }
    }
};