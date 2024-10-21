#ifndef SENSORLOGIC_H
#include <Arduino.h>

#define PIR_SENSOR_PIN_1 15  // Pin für den ersten PIR SENSOR

// TLC
#define RED_LIGHT_PIN_1 13    // Pin für die erste rote LED
#define GREEN_LIGHT_PIN_1 12  // Pin für die erste grüne LED
#define RED_LIGHT_PIN_2 14    // Pin für die zweite rote LED
#define GREEN_LIGHT_PIN_2 27  // Pin für die zweite grüne LED

extern unsigned long currentMillis;

void IRAM_ATTR pirISR1();
void initializeMotionSensors();
int handleSensorMotion();
unsigned long handleTrafficLightsWithMillis();
void handleTrafficLights(int switchNum);

#endif