#include <Arduino.h>
#include "MFRC522.h"
#include "SPI.h"
#include "TrafficLightLogic/SensorLogic.h"

void setup()
{
    initializeMotionSensors(32, 14, 12, 27, 26, 13);
}

void loop()
{
    int switchNum = handleSensorMotion(GREEN_LIGHT_PIN_1);
    handleTrafficLights(switchNum, 14, 12, 27, 26, 13);
}
