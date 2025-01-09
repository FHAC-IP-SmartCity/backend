#include "TrafficLightLogic/SensorLogic.h"
#include <SPI.h>
#include <MFRC522.h>

unsigned long currentMillis = 0;
int TLClock = 20000;

// RFID-Reader initialisieren
MFRC522 rfid(SS_PIN, RST_PIN);

// Autorisierte Karten-IDs
const byte authorizedIDs[][7] = {
    {0x4, 0xAD, 0xA1, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0xC9, 0xA7, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0xA6, 0xB2, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0x42, 0x6D, 0xA5, 0x6E, 0x26, 0x81},
    {0x4, 0x8E, 0x61, 0xA6, 0x6E, 0x26, 0x81}};

const int numIDs = sizeof(authorizedIDs) / sizeof(authorizedIDs[0]);

void initializeTrafficLights(int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW)
{
  SPI.begin();

  // Pins konfigurieren
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  rfid.PCD_Init();
  digitalWrite(RED1, HIGH); // Initiale Ampelstellung
}

// Funktion zum Vergleich von Karten-IDs
bool compareIDs(const byte *id1, const byte *id2, byte length)
{
  for (byte i = 0; i < length; i++)
  {
    if (id1[i] != id2[i])
      return false;
  }
  return true;
}

// Funktion zur Verarbeitung von RFID-Karten
int handleSensorMotion(int GREEN1)
{
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    byte readID[7] = {0};
    for (byte i = 0; i < rfid.uid.size && i < 7; i++)
    {
      readID[i] = rfid.uid.uidByte[i];
    }

    Serial.print("Gelesene Karte: ");
    for (byte i = 0; i < 7; i++)
    {
      Serial.print(readID[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Überprüfen, ob die Karte autorisiert ist
    for (int i = 0; i < numIDs; i++)
    {
      if (compareIDs(readID, authorizedIDs[i], 7))
      {
        Serial.println("Karte autorisiert!");
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();

        if (digitalRead(GREEN1) == HIGH)
        {
          return 2; // Ampel 1 ist grün
        }
        else
        {
          return 3; // Ampel 1 ist rot
        }
      }
    }

    Serial.println("Karte nicht autorisiert.");
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
  case 1: // Zeit verlängern
    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);
    lastSwitchMillis = currentMillis;
    break;

  case 2:
    break;

  case 3: // Ampeln umschalten
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
