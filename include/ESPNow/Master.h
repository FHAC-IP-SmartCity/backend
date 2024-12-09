#pragma once

#include "ESPNow/ESPNowDevice.h"
#include "BusLogic/RFIDReader.h"
#include "pipeline.h"

class ESPNowMaster
{
public:
    ESPNowMaster(const uint8_t *slaveMac, int rfidSdaPin, int rfidSclPin);
    void init();
    void loop();

private:
    ESPNowDevice device;
    RFIDReader rfidReader;
    static void onReceive(const uint8_t *mac, const uint8_t *data, int len);
};
