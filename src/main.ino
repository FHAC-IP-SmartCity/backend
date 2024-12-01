#include <Arduino.h>

#include "Sensors/TCRT5000Sensor.h"
// #include "Sensors/MicrophoneSensor.h"
// #include "Sensors/PhotoResistor.h"
// #include "Sensors/Thermistor.h"

// #include "MACReader.h"
#include "pipeline.h"
TCRT5000Sensor TCRT;
// MicrophoneSensor micSensor;
// Thermistor thermistor;
// PhotoResistor photoResistor;

int TCRTVal = 0;

void setup()
{
    pipeline.open();
    TCRT.init();

    // micSensor.init();
    // thermistor.init();
    // photoResistor.init();
    // macReader.MACinit();
}

void loop()
{
    TCRT.read();

    // Daten aus dem Buffer holen
    TCRTVal = TCRT.getTCRTValue();
    // Daten an den Server senden, wenn Daten vorhanden sind
    // float to double
    pipeline.println(static_cast<double>(TCRTVal));

    // Daten von den Sensoren auslesen
    // bme680.read(sensorData);
    // bh1750.read(sensorData);
    // tcrt5000.read(sensorData);
    // micSensor.read(sensorData);
    // thermistor.readData(sensorData);
    // photoResistor.readData(sensorData);

    // macReader.readMACAddress();

    // Buffer leeren, nach einmaliger Ausgabe
    delay(3000);
}