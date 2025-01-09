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
    sndTrain.read();
    fstPark.read();
    sndPark.read();
    trdPark.read();

    fstTrainNum = fstTrain.getTCRTValue();
    sndTrainNum = sndTrain.getTCRTValue();
    fstParkNum = fstPark.getTCRTValue();
    sndParkNum = sndPark.getTCRTValue();
    trdParkNum = trdPark.getTCRTValue();

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

    if (fstTrainNum > 2000 && sndTrainNum > 2000)
    {
        Serial.println("All trains are in the station");
    }
    else if (sndTrainNum > 2000)
    {
        Serial.println("Train driving in the station");
    }

    if (digitalRead(pirPin) == HIGH)
    {
        digitalWrite(ledPin, HIGH);
        Serial.println("Motion detected");
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }

    delay(1000);
}
