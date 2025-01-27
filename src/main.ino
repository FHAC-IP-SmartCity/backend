#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#include "pipeline.h"

// Instanzen der Sensoren erstellen
BH1750 lightMeter;
Adafruit_BME680 bme; // BME680-Sensor

// Pin-Konfiguration für LEDs
const int LED1 = 25;
const int LED2 = 26;
const int LED3 = 27;
const int LED4 = 14;

// Funktion zum Setzen der LED-Helligkeit
void setLEDs(int brightness)
{
    analogWrite(LED1, brightness);
    analogWrite(LED2, brightness);
    analogWrite(LED3, brightness);
    analogWrite(LED4, brightness);
}

void setup()
{
    Wire.begin(21, 22); // I2C-Pins für ESP32 (SDA=21, SCL=22)

    // BH1750 initialisieren
    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        pipeline.println("BH1750 ready");
    }
    else
    {
        pipeline.println("BH1750 not detected. Check wiring!");
        while (1)
            ;
    }

    // BME680 initialisieren
    if (!bme.begin(0x77))
    { // Adresse 0x77 verwenden
        pipeline.println("BME680 not detected. Check wiring!");
        while (1)
            ;
    }

    // BME680 konfigurieren
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320°C für 150 ms

    // LED-Pins als Ausgang definieren
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // LEDs initial ausschalten
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);

    pipeline.open();
}

void loop()
{

    if (!pipeline.ping())
    {
        pipeline.open();
    }

    // Lux-Wert vom BH1750 lesen
    float lux = lightMeter.readLightLevel();

    // BME680-Daten lesen
    if (!bme.performReading())
    {
        pipeline.println("BME680 Reading Failed!");
        return;
    }

    if (lux > 400)
    {
        // Hohe Lichtintensität → LEDs aus
        setLEDs(0);
        pipeline.send(4410, static_cast<int64_t>(1));
    }
    else if (lux > 200)
    {
        // Mittlere Lichtintensität → LEDs auf mittlerer Helligkeit
        setLEDs(64);
        pipeline.send(4410, static_cast<int64_t>(1));
    }
    else
    {
        // Geringe Lichtintensität → LEDs auf voller Helligkeit
        setLEDs(255);
        pipeline.send(4410, static_cast<int64_t>(0));
    }

    pipeline.send(4511, static_cast<float>(bme.temperature));
    pipeline.send(4513, static_cast<float>(bme.humidity));
    pipeline.send(4514, static_cast<int64_t>(bme.pressure));
    pipeline.send(4512, static_cast<int64_t>(bme.gas_resistance));

    delay(500);
}

// ------------------------------------------------------------------------------------------
// verbindung
// ------------------------------------------------------------------------------------------

// LED1 P25;
// LED2 P26;
// LED3 P27;
// LED4 P14;
// SDA beide mit  P21;
// SCL beide mit  P22;
// BME680 VCC 5v;
// BH1750 VCC 3.3;