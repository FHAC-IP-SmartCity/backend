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

    if (fstTrainNum > 2000 && sndTrainNum > 2000)
    {
        pipeline.println("All trains are in the station");
        // TODO send bool1: true to server
        // TODO send bool2: true to server
    }
    else if (sndTrainNum > 2000)
    {
        pipeline.println("Train driving in the station");
        // TODO send bool: true to server
    }

    if (digitalRead(pirPin) == HIGH)
    {
        digitalWrite(ledPin, HIGH);
        pipeline.println("Motion detected");
        // TODO send bool: true to server
    }
    else
    {
        digitalWrite(ledPin, LOW);
        // TODO send bool: false to server
    }

    if (fstParkNum > 2000)
    {
        pipeline.println("First parking spot is occupied");
        // TODO send bool: true to server
    }
    else
    {
        // TODO send bool: false to server
    }
    if (sndParkNum > 2000)
    {
        pipeline.println("Second parking spot is occupied");
        // TODO send bool: true to server
    }
    else
    {
        // TODO send bool: false to server
    }
    if (trdParkNum > 2000)
    {
        pipeline.println("Third parking spot is occupied");
        // TODO send bool: true to server
    }
    else
    {
        // TODO send bool: false to server
    }

    delay(1000);
}
