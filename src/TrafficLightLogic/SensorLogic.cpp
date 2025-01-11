#include "TrafficLightLogic/SensorLogic.h"

// initialize the RFID reader
MFRC522 rfid(SS_PIN, RST_PIN);

unsigned long currentMillis = 0;

// Function to initialize the traffic lights
void initializeTrafficLights(int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW)
{
  SPI.begin();

  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  rfid.PCD_Init();
  digitalWrite(RED1, HIGH);
}

// Function checks if RFID card is authorized
int authorizeRfidCard(int GREEN1, const byte authorizedIDs[][7])
{

  const int numIDs = sizeof(authorizedIDs) / sizeof(authorizedIDs[0]);

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    byte readID[7] = {0};
    for (byte i = 0; i < rfid.uid.size && i < 7; i++)
    {
      readID[i] = rfid.uid.uidByte[i];
    }

    // Check if the ID is authorized
    for (int i = 0; i < numIDs; i++)
    {
      if (compareIDs(readID, authorizedIDs[i], 7))
      {
        pipeline.println("Karte autorisiert.");

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();

        if (digitalRead(GREEN1) == HIGH) // Traffic light is green
        {
          // TODO: Add send int to frontend
          // pipeline.send(1100, static_cast<int64_t>(2));
          return 2;

          // TODO: Could be 1 as well
          // pipeline.send(1100, static_cast<int64_t>(1));
          // return 1;
        }
        else // Traffic light is red
        {
          // TODO: Add send int to frontend
          // pipeline.send(1100, static_cast<int64_t>(3));
          return 3;
        }
      }
    }

    pipeline.println("Karte nicht autorisiert.");
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  return 0;
}

// Function to handle the traffic lights
void handleTrafficLights(int switchNum, int TLClock, int RED1, int GREEN1, int RED2, int GREEN2, int YELLOW)
{
  static unsigned long lastSwitchMillis = 0;
  currentMillis = millis();

  switch (switchNum)
  {
  case 1: // Expand time for green light
    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);
    lastSwitchMillis = currentMillis;
    break;

  case 2: // Ignore RFID card
    break;

  case 3: // Switch to other traffic light
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

  default: // Switch traffic light after TLClock
    if (currentMillis - lastSwitchMillis >= TLClock)
    {
      // TODO: Add send int to frontend
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

    // pipeline.send(1100, static_cast<int64_t>(4));
    break;
  }
}

// Function to compare card IDs
bool compareIDs(const byte *id1, const byte *id2, byte length)
{
  for (byte i = 0; i < length; i++)
  {
    if (id1[i] != id2[i])
      return false;
  }
  return true;
}