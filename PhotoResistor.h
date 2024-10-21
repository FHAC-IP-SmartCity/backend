#ifndef PHOTORESISTOR_H
#include <Arduino.h>

#define PHOTO_RESISTOR_PIN 34
#define RED_PIN 25
#define BLUE_PIN 26
#define GREEN_PIN 27
#define LIGHT_THRESHOLD 1500

void setupPhotoResistor();
void photoResistorLogic();

#endif
