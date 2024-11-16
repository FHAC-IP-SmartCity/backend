#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h>
#include "SensorLogic.h"
#include "PhotoResistor.h"
#include "Thermistor.h"
#include "config.h"

// Dashboard
int counter1 = 0;
int counter2 = 0;

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

#define FIREBASE_HOST FIREBASE_API_HOST
#define FIREBASE_AUTH FIREBASE_API_TOKEN

void setup()
{
  { // PinMode
    initializeMotionSensors(32, 27, 12, 25, 26, 14);
    Serial.begin(115200);
  }

  { // Wifi-Config
    WiFi.begin("Amier", "nxkx4920");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Connected to Wi-Fi");
  }

  { // Firebase-Config
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    if (Firebase.ready())
    {
      Serial.println("Connected to Firebase");
    }
    else
    {
      Serial.println("Failed to connect to Firebase");
    }
  }
}

void loop()
{
  handleTrafficLights(handleSensorMotion(12), 27, 12, 25, 26, 14);
}
