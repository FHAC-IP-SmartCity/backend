#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <BH1750.h>

#include "Sensors/BME680Sensor.h"
#include "Sensors/BH1750Sensor.h"
#include "Sensors/TCRT5000Sensor.h"
#include "Sensors/MicrophoneSensor.h"

#include "BusLogic/CardRead.h"
#include "pipeline.h"

SensorData sensorData;
BME680Sensor bme680;
BH1750Sensor bh1750;
TCRT5000Sensor tcrt5000;
MicrophoneSensor micSensor;

void setup()
{
  Serial.begin(115200);
  pipeline.open();
  setupRFIDRead();

  bme680.init();
  bh1750.init();
  tcrt5000.init();
  micSensor.init();
}

void loop()
{
  if (!pipeline.isOpen())
  {
    pipeline.open();
  }
  readDataFromCard();

  // Daten von den Sensoren auslesen
  bme680.read(sensorData);
  bh1750.read(sensorData);
  tcrt5000.read(sensorData);
  micSensor.read(sensorData);
  delay(3000);
}