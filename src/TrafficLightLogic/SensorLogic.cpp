#include "TrafficLightLogic/SensorLogic.h"

volatile bool fstMotionDetected = false;
volatile bool sndMotionDetected = false;
unsigned long currentMillis = 0;
int TLClock = 20000;

// Initialisiere die Bewegungssensoren
void initializeMotionSensors(int PIR, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW)
{
  // Config Pins
  pinMode(PIR, INPUT);
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  // Config Interrupts
  attachInterrupt(digitalPinToInterrupt(PIR), pirISR1, RISING);
  digitalWrite(RED1, HIGH);
}

// ISR
void IRAM_ATTR pirISR1()
{
  fstMotionDetected = true;
}

// hanldes the motion sensor
int handleSensorMotion(int GREEN1)
{
  if (fstMotionDetected)
  {
    int switchNum = 0;

    // Check which traffic light is green
    bool fstTLGreen = digitalRead(GREEN1) == HIGH;

    // Check if more than 7 seconds have passed
    // True if more than 7 seconds have passed
    bool fstTimer = handleTrafficLightsWithMillis() % TLClock >= 15000;

    if (fstTLGreen && fstTimer && !sndMotionDetected)
    {
      // Ampel 1 ist grün und mehr als 7 Sekunden sind vergangen - Zeit verlängern
      switchNum = 1;
      pipeline.println("Extending time");
    }
    else if (((fstTLGreen && !fstTimer) || (!fstTLGreen && fstTimer)) && !sndMotionDetected)
    {
      // Ampel 1 ist grün und weniger als 7 Sekunden sind vergangen - Keine Aktion erforderlich
      switchNum = 2;
      pipeline.println("Ignoring motion");
    }
    else if (!fstTLGreen && !fstTimer && !sndMotionDetected)
    {
      // Ampel 2 ist grün und weniger als 7 Sekunden sind vergangen - Switch lights
      switchNum = 3;
      pipeline.println("Switch lights");
    }
    else
    {
      // Standardfall: Falls keine der obigen Bedingungen zutrifft
      switchNum = 0;
      pipeline.println("Default case");
    }

    fstMotionDetected = false;
    pipeline.println("Switch Number: ");
    pipeline.println(String(switchNum).c_str());
    return switchNum;
  }

  return 0;
}

// Behandle die Ampelsteuerung mit Millisekunden
unsigned long handleTrafficLightsWithMillis()
{
  currentMillis = millis();
  static unsigned long previousMillis = 0;
  if (currentMillis - previousMillis >= TLClock)
  {
    previousMillis = currentMillis;
  }
  return currentMillis;
}

void handleTrafficLights(int switchNum, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW)
{
  static unsigned long lastSwitchMillis = 0;
  currentMillis = millis();

  switch (switchNum)
  {
  case 1:
    // Extend time
    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);
    lastSwitchMillis = currentMillis;
    break;

  case 2:
    break;
  case 3:
    // Switch lights
    digitalWrite(GREEN1, LOW);
    digitalWrite(GREEN2, LOW);
    digitalWrite(YELLOW, HIGH);
    delay(3000);
    digitalWrite(YELLOW, LOW);

    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);
    lastSwitchMillis = currentMillis;
    break;

  default:
    if (currentMillis - lastSwitchMillis >= 20000)
    {
      // Default case
      digitalWrite(GREEN1, LOW);
      digitalWrite(GREEN2, LOW);
      digitalWrite(YELLOW, HIGH);
      delay(3000);
      digitalWrite(YELLOW, LOW);

      if (digitalRead(RED2) == HIGH)
      {
        digitalWrite(GREEN1, LOW);
        digitalWrite(RED1, HIGH);
        digitalWrite(GREEN2, HIGH);
        digitalWrite(RED2, LOW);
      }
      else
      {
        digitalWrite(GREEN1, HIGH);
        digitalWrite(RED1, LOW);
        digitalWrite(GREEN2, LOW);
        digitalWrite(RED2, HIGH);
      }
      lastSwitchMillis = currentMillis;
      break;
    }
  }
}