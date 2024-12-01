#include <Arduino.h>
#include "ESPNow/Master.h"
#include "ESPNow/Slave.h"
#include "pipeline.h"

// MAC-Adressen
uint8_t slaveMac1[] = {0xA0, 0xB7, 0x65, 0x2D, 0x5C, 0x2C}; // MAC-Adresse des Slaves
// uint8_t masterMac[] = {0x3C, 0x71, 0xBF, 0x0F, 0x4C, 0x84}; // MAC-Adresse des Masters

// Master und Slave Instanzen
ESPNowMaster master(slaveMac1, 21, 22); // SDA: Pin 21, SCL: Pin 22
// ESPNowSlave slave(masterMac);

void setup()
{
    pipeline.open();

    master.init();
    // slave.init();
}

void loop()
{
    master.loop();
    // slave.loop();
}
