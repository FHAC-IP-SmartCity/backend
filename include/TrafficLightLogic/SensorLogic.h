#ifndef SENSORLOGIC_H
#include <Arduino.h>
#include "SPI.h"
#include "MFRC522.h"

#define RST_PIN 17 // 22 Pin für den Reset
#define SS_PIN 5   // 21 Pin

extern unsigned long currentMillis;

void initializeTrafficLights(int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW);
int handleSensorMotion(int GREEN1);
unsigned long handleTrafficLightsWithMillis();
void handleTrafficLights(int switchNum, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW);

#endif