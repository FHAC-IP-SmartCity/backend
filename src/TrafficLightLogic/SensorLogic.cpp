#include "TrafficLightLogic/SensorLogic.h"
#include <SPI.h>
#include <MFRC522.h>

// Pins für RFID
#define RST_PIN 22
#define SS_PIN 21

volatile bool fstMotionDetected = false;
unsigned long currentMillis = 0;
int TLClock = 20000;

// RFID-Reader initialisieren
MFRC522 rfid(SS_PIN, RST_PIN);

// Autorisierte Karten-ID
const String authorizedCardID = "745acf5b";
const String authorizedCardID2 = "b0e3f7b1";

void initializeMotionSensors(int PIR, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW)
{
  SPI.begin();

  // Config Pins
  pinMode(PIR, INPUT);
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  rfid.PCD_Init();
  digitalWrite(RED1, HIGH);
}

int handleSensorMotion(int GREEN1)
{
  // Prüfen, ob eine Karte erkannt wurde
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    // Karten-ID auslesen
    String cardID = "";
    for (byte i = 0; i < rfid.uid.size; i++)
    {
      cardID += String(rfid.uid.uidByte[i], HEX);
    }

    Serial.println("RFID Card ID: " + cardID);

    // Karten-ID vergleichen
    if (cardID.equalsIgnoreCase(authorizedCardID) && digitalRead(GREEN1) == HIGH)
    {
      Serial.println("Authorized card detected!");
      return 2; // Ignore the motion sensor
    }
    else if (cardID.equalsIgnoreCase(authorizedCardID) && digitalRead(GREEN1) == LOW)
    {
      Serial.println("Authorized card detected!");
      return 3; // Schalte die Ampel
    }
    else
    {
      Serial.println("Unauthorized card detected.");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  return 0;
}

// Ampelsteuerung mit Millisekunden
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
    // Schalte die Ampel
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
    }
    break;
  }
}
