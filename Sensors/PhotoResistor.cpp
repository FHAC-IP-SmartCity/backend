#include "PhotoResistor.h"

#define MAX_LIGHT_LEVEL 4095   // Maximaler Wert bei 12-Bit ADC
#define MIN_LIGHT_LEVEL 0      // Minimaler Wert

void setupPhotoResistor() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);  // Du kannst das Grün auch hinzufügen, wenn du möchtest.
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(PHOTO_RESISTOR_PIN, INPUT);
}

void photoResistorLogic() {
  int lightLevel = analogRead(PHOTO_RESISTOR_PIN);  // Lichtintensität messen
  Serial.println(lightLevel);  // Debug

  // Den Lichtwert normalisieren auf einen Bereich von 0 bis 255 (für PWM)
  int normalizedLight = map(lightLevel, MIN_LIGHT_LEVEL, MAX_LIGHT_LEVEL, 0, 255);

  // Blau wird stärker, wenn es heller ist
  int blueValue = normalizedLight;  // Blau ist direkt proportional zur Helligkeit
  
  // Rot wird stärker, wenn es dunkler wird (invertierter Wert von Blau)
  int redValue = 255 - normalizedLight;  // Rot ist umgekehrt proportional
  
  // RGB-LED ansteuern mit PWM
  analogWrite(BLUE_PIN, blueValue);
  analogWrite(RED_PIN, redValue);
  
  // Optional: falls du auch Grün verwenden möchtest (kann z.B. für mittlere Helligkeit verwendet werden)
  // analogWrite(GREEN_PIN, (redValue + blueValue) / 2);

  delay(1000);  // Kleine Pause
}
