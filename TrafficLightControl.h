#ifndef TrafficLightControl_h
#define TrafficLightControl_h

#include <Arduino.h>

#define RED_LIGHT_PIN_1 13    // Pin für die erste rote LED
#define GREEN_LIGHT_PIN_1 12  // Pin für die erste grüne LED
#define RED_LIGHT_PIN_2 14    // Pin für die zweite rote LED
#define GREEN_LIGHT_PIN_2 27  // Pin für die zweite grüne LED


void initializeTrafficLights();
void handleTrafficLights();

#endif
