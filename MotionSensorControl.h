#ifndef MotionSensorControl_h
#define MotionSensorControl_h

#include <Arduino.h>
#include "TrafficLightControl.h"

#define PIR_SENSOR_PIN_1 15  // Pin für den ersten PIR SENSOR
#define PIR_SENSOR_PIN_2 2    // Pin für den zweiten PIR SENSOR


void pirISR1();
void pirISR2();


void initializeMotionSensors();
void processMotionSensors();
void switchTrafficLight(int sensor);

#endif
