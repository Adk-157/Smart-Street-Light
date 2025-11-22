#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define SS 10
#define RST 9
#define DIO0 2

int status = 0;        
int brightness = 50;
int lastStatus = -1;
int lastBrightness = -1;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!Serial);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Initialization Failed!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = LoRa.readString();
    Serial.println("Received via LoRa: " + receivedData);

    int commaIndex = receivedData.indexOf(',');
    if (commaIndex > 0) {
      status = receivedData.substring(0, commaIndex).toInt();
      brightness = receivedData.substring(commaIndex + 1).toInt();

      // Send data only if it changes
      if (status != lastStatus || brightness != lastBrightness) {
        Wire.beginTransmission(8);
        Wire.write(status);
        Wire.write(brightness);
        Wire.endTransmission();

        lastStatus = status;
        lastBrightness = brightness;

        Serial.println("Data Sent to Slave");
      }
    } else {
      Serial.println("Invalid data format");
    }
  }
}