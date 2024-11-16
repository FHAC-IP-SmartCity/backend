#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h>
#include "SensorLogic.h"
#include "PhotoResistor.h"
#include "Thermistor.h"

// Dashboard
int counter1 = 0;
int counter2 = 0;

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
require('dotenv').config();
const host = process.env.FIREBASE_API_HOST;
const token = process.env.FIREBASE_API_TOKEN;

#define FIREBASE_HOST host
#define FIREBASE_AUTH token

void setup() {
  {  //PinMode
    initializeMotionSensors();
    Serial.begin(115200);
  }

  {  // Wifi-Config
    WiFi.begin("Amier", "nxkx4920");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Connected to Wi-Fi");
  }

  {  // Firebase-Config
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    if (Firebase.ready()) {
      Serial.println("Connected to Firebase");
    } else {
      Serial.println("Failed to connect to Firebase");
    }
  }
}

void loop() {
  handleTrafficLights(handleSensorMotion());
}
