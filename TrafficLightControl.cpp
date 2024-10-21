#include "TrafficLightControl.h"

 
void initializeTrafficLights() {
    pinMode(RED_LIGHT_PIN_1, OUTPUT);
    pinMode(GREEN_LIGHT_PIN_1, OUTPUT);
    pinMode(RED_LIGHT_PIN_2, OUTPUT);
    pinMode(GREEN_LIGHT_PIN_2, OUTPUT);
}



void handleTrafficLights() {
    static unsigned long lastChange = 0;


    // Example of using millis() to handle timing instead of delay()
    if (lastChange >= 10000) {  // 10 second interval


        Serial.println("Toggle the lights");
        if (digitalRead(RED_LIGHT_PIN_1) == HIGH) {
            digitalWrite(RED_LIGHT_PIN_1, LOW);
            digitalWrite(GREEN_LIGHT_PIN_1, HIGH);
            digitalWrite(RED_LIGHT_PIN_2, HIGH);
            digitalWrite(GREEN_LIGHT_PIN_2, LOW);
        } else {
            digitalWrite(RED_LIGHT_PIN_1, HIGH);
            digitalWrite(GREEN_LIGHT_PIN_1, LOW);
            digitalWrite(RED_LIGHT_PIN_2, LOW);
            digitalWrite(GREEN_LIGHT_PIN_2, HIGH);
        }
    }
}