#include <Wire.h>

#define I2C_SLAVE_ADDR 8
#define DIMMER_PIN 5   // PWM pin controlling Hyovis module (D5 recommended)

int statusValue = 0;
int brightnessValue = 0;

// Hyovis expects 0–255 PWM (0 = full OFF, 255 = full ON)
// We'll map brightness (0–100) -> 0–255
int convertBrightness(int b) {
  return map(b, 0, 100, 0, 255);
}

void receiveEvent(int howMany) {
  if (howMany == 2) {
    statusValue = Wire.read();       // byte 1 -> status
    brightnessValue = Wire.read();   // byte 2 -> brightness
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DIMMER_PIN, OUTPUT);

  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onReceive(receiveEvent);

  Serial.println("I2C Slave Ready. Waiting for Master...");
}

void loop() {
  static int lastStatus = -1;
  static int lastBrightness = -1;

  // change detection
  if (statusValue != lastStatus || brightnessValue != lastBrightness) {

    Serial.print("Received -> Status: ");
    Serial.print(statusValue);
    Serial.print(" | Brightness: ");
    Serial.println(brightnessValue);

    if (statusValue == 0) {
      // Power OFF the dimmer
      analogWrite(DIMMER_PIN, 0);  
      Serial.println("Street Light OFF");
    } 
    else {
      // Convert 0–100% brightness → PWM duty cycle
      int pwmValue = convertBrightness(brightnessValue);
      analogWrite(DIMMER_PIN, pwmValue);
      Serial.print("Updated PWM -> ");
      Serial.println(pwmValue);
    }

    lastStatus = statusValue;
    lastBrightness = brightnessValue;
  }

  delay(10);
}
