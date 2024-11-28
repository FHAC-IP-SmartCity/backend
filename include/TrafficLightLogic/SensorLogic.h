#ifndef SENSORLOGIC_H
#include <Arduino.h>
#include "pipeline.h"

#define PIR_SENSOR_PIN_1 32 // 15 Pin für den ersten PIR SENSOR

#define RED_LIGHT_PIN_1 27   // 22 Pin für die erste rote LED
#define GREEN_LIGHT_PIN_1 12 // 19 Pin für die erste grüne LED
#define RED_LIGHT_PIN_2 25   // 21 Pin für die zweite rote LED
#define GREEN_LIGHT_PIN_2 26 // 18 Pin für die zweite grüne LED
#define YELLOW_LIGHT_PIN 14  // 5 Pin für die gelbe LED

extern unsigned long currentMillis;

void IRAM_ATTR pirISR1();
void initializeMotionSensors(int PIR, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW);
int handleSensorMotion(int GREEN1);
unsigned long handleTrafficLightsWithMillis();
void handleTrafficLights(int switchNum, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW);

#endif