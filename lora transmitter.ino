#include <SPI.h>
#include <LoRa.h>

#define SS 10 // Pin for LoRa chip select (may differ based on your hardware setup)
#define RST 9 // Pin for LoRa reset
#define DIO0 2 // Pin for LoRa DIO0

void setup() {
Serial.begin(9600); // Serial Monitor for debugging
while (!Serial);

6

// Initialize LoRa module
if (!LoRa.begin(868E6)) { // Set the frequency to 433 MHz (use 868E6 for Europe, 915E6
for the USA)
Serial.println("Starting LoRa failed!");
while (1);
}

Serial.println("LoRa Transmitter Initialized");
}

void loop() {
// Check if data is received from Raspberry Pi via Serial (from Python script)
if (Serial.available() > 0) {
String dataFromPi = Serial.readStringUntil('\n'); // Read data from Raspberry Pi
Serial.print("Received from Raspberry Pi: ");
Serial.println(dataFromPi); // Print data for debugging

// Send data via LoRa
LoRa.beginPacket();
LoRa.print(dataFromPi); // Transmit data
LoRa.endPacket(); // End transmission

Serial.println("Data transmitted via LoRa.");

7

}
}