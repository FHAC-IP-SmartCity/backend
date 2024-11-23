#ifndef PHOTORESISTOR_H
#include <Arduino.h>

#define PHOTO_RESISTOR_PIN 36 //34
#define RED_PIN 0 //25
#define BLUE_PIN 0 //26
#define GREEN_PIN 0 //27
#define LIGHT_THRESHOLD 1500

//TODO: Automatisieren durch bessere Pinbelegung
void setupPhotoResistor();
void photoResistorLogic();

#endif
