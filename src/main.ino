#include <Arduino.h>
#include "MFRC522.h"
#include "SPI.h"
#include "TrafficLightLogic/SensorLogic.h"

void setup()
{
    initializeTrafficLights(14, 12, 27, 26, 13);
}

void loop()
{
    int switchNum = handleSensorMotion(12);
    handleTrafficLights(switchNum, 14, 12, 27, 26, 13);
}
