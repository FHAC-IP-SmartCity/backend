#include <Arduino.h>
#include "Sensors/TCRT5000.h"

#define NUM_SENSORS 5
#define PIR_PIN 13
#define LED_PIN 17

// Pins                            Train1 Train2 Park1 Park2 Park3
const int sensorPins[NUM_SENSORS] = {12, 14, 27, 26, 25};
TCRT sensors[NUM_SENSORS];
int sensorValues[NUM_SENSORS] = {0};

void setup()
{
    pinMode(PIR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    pipeline.open();

    // Initialize all sensors
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        sensors[i].init(sensorPins[i]);
    }
}

void loop()
{
    // Read all sensors
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        sensors[i].read();
        sensorValues[i] = sensors[i].getTCRTValue();
    }

    // Train detection
    if (sensorValues[0] >= 3000 && sensorValues[1] >= 3000)
    {
        pipeline.println("All trains are in the station");

        pipeline.send(2210, static_cast<int64_t>(1));
        pipeline.send(2220, static_cast<int64_t>(1));
    }
    else if (sensorValues[1] >= 3000)
    {
        pipeline.println("Train driving in the station");
        pipeline.send(2220, static_cast<int64_t>(1));
        pipeline.send(2210, static_cast<int64_t>(0));
    }
    else
    {
        pipeline.send(2210, static_cast<int64_t>(0));
        pipeline.send(2220, static_cast<int64_t>(0));
    }

    // Parking spot detection
    for (int i = 2; i < NUM_SENSORS; i++)
    {
        if (sensorValues[i] >= 1)
        {
            pipeline.println((String("Parking spot ") + (i - 1) + " is occupied").c_str());
            pipeline.send(2230 + (i - 2) * 10, static_cast<int64_t>(1));
        }
        else
        {
            pipeline.send(2230 + (i - 2) * 10, static_cast<int64_t>(0));
        }
    }

    // PIR sensor motion detection
    if (digitalRead(PIR_PIN) == HIGH)
    {
        digitalWrite(LED_PIN, HIGH);
        pipeline.println("Motion detected");
        pipeline.send(2310, static_cast<int64_t>(1));
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
        pipeline.send(2310, static_cast<int64_t>(0));
    }

    delay(1000);
}
