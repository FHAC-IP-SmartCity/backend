#include "esp32-hal-gpio.h"
#include "MotionSensorControl.h"

extern volatile unsigned long motionTime1 = 0;  // Zeit für Sensor 1
extern volatile unsigned long motionTime2 = 0;  // Zeit für Sensor 2
extern volatile bool motionDetected1 = false;
extern volatile bool motionDetected2 = false;

void initializeMotionSensors() {
  pinMode(PIR_SENSOR_PIN_1, INPUT);
  pinMode(PIR_SENSOR_PIN_2, INPUT);

  // Konfiguriere Interrupts
  attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN_1), pirISR1, RISING);
  attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN_2), pirISR2, RISING);
}

// Interrupt-Service-Routine (ISR) für den ersten Sensor

void pirISR1() {

  //TL Check
  if (digitalRead(GREEN_LIGHT_PIN_1) == HIGH) {
    //Time Check
    /*if ((currentMillis % 10) < 3) {
      motionDetected1 = true;
      motionTime1 = millis();
      switchTrafficLight(1);
    }
  } else {
    if ((currentMillis % 10) > 3) {
      motionDetected1 = true;
      motionTime1 = millis();
      switchTrafficLight(1);
    }*/
      motionDetected1 = true;
      motionTime1 = millis();
      switchTrafficLight(1);
  }
}

void pirISR2() {

  //TL Check
  if (digitalRead(GREEN_LIGHT_PIN_2) == HIGH) {
    //Time Check
    /*if ((currentMillis % 10) < 3) {
      motionDetected2 = true;
      motionTime2 = millis();
      switchTrafficLight(2);
    }
  } else {
    if ((currentMillis % 10) > 3) {
      motionDetected2 = true;
      motionTime2 = millis();
      switchTrafficLight(2);
    }*/
      motionDetected2 = true;
      motionTime2 = millis();
      switchTrafficLight(2);
  }
}

void switchTrafficLight(int sensorId) {
  if (sensorId == 1) {
    // Logic for switching traffic lights when Sensor 1 detects motion
    digitalWrite(RED_LIGHT_PIN_1, LOW);
    digitalWrite(GREEN_LIGHT_PIN_1, HIGH);
    digitalWrite(RED_LIGHT_PIN_2, HIGH);
    digitalWrite(GREEN_LIGHT_PIN_2, LOW);
    delay(3000);
  } else if (sensorId == 2) {
    // Logic for switching traffic lights when Sensor 2 detects motion
    digitalWrite(RED_LIGHT_PIN_1, HIGH);
    digitalWrite(GREEN_LIGHT_PIN_1, LOW);
    digitalWrite(RED_LIGHT_PIN_2, LOW);
    digitalWrite(GREEN_LIGHT_PIN_2, HIGH);
    delay(3000);
  }
}

void processMotionSensors() {
  unsigned long c2urrentMillis = millis();

  // Example of handling additional logic
  if (motionDetected1 && (c2urrentMillis - motionTime1 > 3000)) {
    motionDetected1 = false;  // Reset after processing
  }
  if (motionDetected2 && (c2urrentMillis - motionTime2 > 3000)) {
    motionDetected2 = false;  // Reset after processing
  }
}
