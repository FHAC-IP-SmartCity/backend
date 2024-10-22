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

#define FIREBASE_HOST "ip-test-329c7-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "H904ZEzTA0YE1j6dkxC0u8VcXtRI6fUeSYsGmfAC"

void setup() {
  {  //PinMode
    initializeMotionSensors();
    setupPhotoResistor();
    setupThermistor();
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
  // Photoresistor
  photoResistorLogic();
  thermistorLogic();
  handleTrafficLights(handleSensorMotion());
}
