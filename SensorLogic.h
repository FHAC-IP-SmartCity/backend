#ifndef SENSORLOGIC_H
#include <Arduino.h>

#define PIR_SENSOR_PIN_1 15  // Pin für den ersten PIR SENSOR

#define RED_LIGHT_PIN_1 22    // Pin für die erste rote LED
#define GREEN_LIGHT_PIN_1 19  // Pin für die erste grüne LED
#define RED_LIGHT_PIN_2 21   // Pin für die zweite rote LED
#define GREEN_LIGHT_PIN_2 18  // Pin für die zweite grüne LED
#define YELLOW_LIGHT_PIN 5    // Pin für die gelbe LED

extern unsigned long currentMillis;

void IRAM_ATTR pirISR1();
void initializeMotionSensors();
int handleSensorMotion();
unsigned long handleTrafficLightsWithMillis();
void handleTrafficLights(int switchNum);

#endif