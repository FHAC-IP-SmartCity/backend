#include <Arduino.h>
#include <unity.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setUp(void)
{
    Wire.begin();
    lightMeter.begin();
}

void tearDown(void)
{
    // Clean up code if needed
}

void test_light_sensor_initialization(void)
{
    TEST_ASSERT_TRUE(lightMeter.begin());
}

void test_light_sensor_reading(void)
{
    float lux = lightMeter.readLightLevel();
    TEST_ASSERT_TRUE(lux >= 0.0);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_light_sensor_initialization);
    RUN_TEST(test_light_sensor_reading);
    UNITY_END();
}

void loop()
{
    // Empty loop
}