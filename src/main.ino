#include <Arduino.h>
#include "Sensors/TCRT5000.h"

TCRT fstTrain;
TCRT sndTrain;
TCRT fstPark;
TCRT sndPark;
TCRT trdPark;

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

    // TODO send data to server

    // Train detection
    if (fstTrainNum >= 1 && sndTrainNum >= 1)
    {
        pipeline.println("All trains are in the station");

        // pipeline.send(2210, static_cast<int64_t>(1));
        // pipeline.send(2220, static_cast<int64_t>(1));
    }
    else if (sndTrainNum >= 1)
    {
        pipeline.println("Train driving in the station");
        // pipeline.send(2220, static_cast<int64_t>(1));
    }
    else
    {
        // pipeline.send(2210, static_cast<int64_t>(0));
        // pipeline.send(2220, static_cast<int64_t>(0));
    }

    // Parking spot detection
    if (fstParkNum >= 1)
    {
        pipeline.println("First parking spot is occupied");
        // pipeline.send(2230, static_cast<int64_t>(1));
    }

    if (sndParkNum >= 1)
    {
        pipeline.println("Second parking spot is occupied");
        // pipeline.send(2240, static_cast<int64_t>(1));
    }

    if (trdParkNum >= 1)
    {
        pipeline.println("Third parking spot is occupied");
        // pipeline.send(2250, static_cast<int64_t>(1));
    }

    else
    {
        // pipeline.send(2230, static_cast<int64_t>(0));
        // pipeline.send(2240, static_cast<int64_t>(0));
        // pipeline.send(2250, static_cast<int64_t>(0));
    }

    // PIR sensor motion detection
    if (digitalRead(pirPin) == HIGH)
    {
        digitalWrite(ledPin, HIGH);
        pipeline.println("Motion detected");
        // pipeline.send(2310, static_cast<int64_t>(1));
    }
    else
    {
        digitalWrite(ledPin, LOW);
        // pipeline.send(2310, static_cast<int64_t>(0));
    }

    delay(1000);
}
