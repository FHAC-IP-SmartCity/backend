#include "SensorLogic.h"
#include "esp32-hal-gpio.h"

volatile bool fstMotionDetected = false;
volatile bool sndMotionDetected = false;
unsigned long currentMillis = 0;
int TLClock = 20000;

// Initialisiere die Bewegungssensoren
void initializeMotionSensors() {
  pinMode(PIR_SENSOR_PIN_1, INPUT);
  // TLC
  pinMode(RED_LIGHT_PIN_1, OUTPUT);
  pinMode(GREEN_LIGHT_PIN_1, OUTPUT);
  pinMode(RED_LIGHT_PIN_2, OUTPUT);
  pinMode(GREEN_LIGHT_PIN_2, OUTPUT);

  // Config Interrupts
  attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN_1), pirISR1, RISING);
  digitalWrite(RED_LIGHT_PIN_1, HIGH);
}

// ISR
void IRAM_ATTR pirISR1() {
  fstMotionDetected = true;
}

// hanldes the motion sensor
int handleSensorMotion() {
  if (fstMotionDetected) {
    int switchNum = 0;

    // Check which traffic light is green
    bool fstTLGreen = digitalRead(GREEN_LIGHT_PIN_1) == HIGH;

    // Check if more than 7 seconds have passed
    // True if more than 7 seconds have passed
    bool fstTimer = handleTrafficLightsWithMillis() % TLClock >= 15000;

    if (fstTLGreen && fstTimer && !sndMotionDetected) {
      // Ampel 1 ist grün und mehr als 7 Sekunden sind vergangen - Zeit verlängern
      switchNum = 1;
      Serial.println("Extending time");
    }
    else if (((fstTLGreen && !fstTimer) || (!fstTLGreen && fstTimer)) && !sndMotionDetected) {
      // Ampel 1 ist grün und weniger als 7 Sekunden sind vergangen - Keine Aktion erforderlich
      switchNum = 2;
      Serial.println("Ignoring motion");
    }
    else if (!fstTLGreen && !fstTimer && !sndMotionDetected) {
      // Ampel 2 ist grün und weniger als 7 Sekunden sind vergangen - Switch lights
      switchNum = 3;
      Serial.println("Switch lights");
    }
    else {
      // Standardfall: Falls keine der obigen Bedingungen zutrifft
      switchNum = 0;
      Serial.println("Default case");
    }

    fstMotionDetected = false;
    Serial.print("Switch Number: ");
    Serial.println(switchNum);
    return switchNum;
  }

  return 0;
}

// Behandle die Ampelsteuerung mit Millisekunden
unsigned long handleTrafficLightsWithMillis() {
  currentMillis = millis();
  static unsigned long previousMillis = 0;
  if (currentMillis - previousMillis >= TLClock) {previousMillis = currentMillis;}
  return currentMillis;
}

void handleTrafficLights(int switchNum) {
  static unsigned long lastSwitchMillis = 0;
  currentMillis = millis();

  switch (switchNum) {
  case 1:
    // Extend time
    digitalWrite(GREEN_LIGHT_PIN_1, HIGH);
    digitalWrite(RED_LIGHT_PIN_1, LOW);
    digitalWrite(GREEN_LIGHT_PIN_2, LOW);
    digitalWrite(RED_LIGHT_PIN_2, HIGH);
    lastSwitchMillis = currentMillis;
    break;

  case 2:
    break;
  case 3:
    // Switch lights
    digitalWrite(GREEN_LIGHT_PIN_1, HIGH);
    digitalWrite(RED_LIGHT_PIN_1, LOW);
    digitalWrite(GREEN_LIGHT_PIN_2, LOW);
    digitalWrite(RED_LIGHT_PIN_2, HIGH);
    lastSwitchMillis = currentMillis;
    break;

  default:
    if (currentMillis - lastSwitchMillis >= 20000) {
      //Default case
      if (digitalRead(GREEN_LIGHT_PIN_1) == HIGH) {
        digitalWrite(GREEN_LIGHT_PIN_1, LOW);
        digitalWrite(RED_LIGHT_PIN_1, HIGH);
        digitalWrite(GREEN_LIGHT_PIN_2, HIGH);
        digitalWrite(RED_LIGHT_PIN_2, LOW);
      }
      else {
        digitalWrite(GREEN_LIGHT_PIN_1, HIGH);
        digitalWrite(RED_LIGHT_PIN_1, LOW);
        digitalWrite(GREEN_LIGHT_PIN_2, LOW);
        digitalWrite(RED_LIGHT_PIN_2, HIGH);
      }
      lastSwitchMillis = currentMillis;
      break;
    }
  }
}