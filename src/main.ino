#include <Arduino.h>
#include "Sensors/TCRT5000Sensor.h"

TCRT5000Sensor fstTrain;
TCRT5000Sensor sndTrain;
TCRT5000Sensor fstPark;
TCRT5000Sensor sndPark;
TCRT5000Sensor trdPark;

#define pirPin 13
#define ledPin 17

int fstTrainNum = 0;
int sndTrainNum = 0;
int fstParkNum = 0;
int sndParkNum = 0;
int trdParkNum = 0;

void setup()
{
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);

    fstTrain.init(12);
    sndTrain.init(14);
    fstPark.init(27);
    sndPark.init(26);
    trdPark.init(25);
}

void loop()
{
    fstTrain.read();
    fstTrainNum = fstTrain.getTCRTValue();
    sndTrain.read();
    sndTrainNum = sndTrain.getTCRTValue();
    fstPark.read();
    fstParkNum = fstPark.getTCRTValue();
    sndPark.read();
    sndParkNum = sndPark.getTCRTValue();
    trdPark.read();
    trdParkNum = trdPark.getTCRTValue();

    if (fstTrainNum >= 1 && sndTrainNum >= 1)
    {
        Serial.println("All trains are in the station");
        // TODO send bool1: true to server
        // TODO send bool2: true to server
    }
    else if (sndTrainNum >= 1)
    {
        Serial.println("Train driving in the station");
        // TODO send bool: true to server
    }

    if (digitalRead(pirPin) == HIGH)
    {
        digitalWrite(ledPin, HIGH);
        Serial.println("Motion detected");
        // TODO send bool: true to server
    }
    else
    {
        digitalWrite(ledPin, LOW);
        // TODO send bool: false to server
    }

    if (fstParkNum >= 1)
    {
        pipeline.println("First parking spot is occupied");
        // TODO send bool: true to server
    }
    else
    {
        // TODO send bool: false to server
    }
    if (sndParkNum >= 1)
    {
        pipeline.println("Second parking spot is occupied");
        // TODO send bool: true to server
    }
    else
    {
        // TODO send bool: false to server
    }
    if (trdParkNum >= 1)
    {
        pipeline.println("Third parking spot is occupied");
        // TODO send bool: true to server
    }
    else
    {
        // TODO send bool: false to server
    }

    Serial.print("Train1: ");
    Serial.println(fstTrainNum);

    Serial.print("Train2: ");
    Serial.println(sndTrainNum);

    Serial.print("Park1: ");
    Serial.println(fstParkNum);

    Serial.print("Park2: ");
    Serial.println(sndParkNum);

    Serial.print("Park3: ");
    Serial.println(trdParkNum);

    delay(1000);
}
