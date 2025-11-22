🏙️ Smart Street Light – Remote LoRa-Based AC Dimming System

A scalable, long-range, edge-driven street-lighting control stack.

🚀 Overview

This project implements a remote-controlled smart street-light system powered by LoRa, I²C, and an AC dimmer (Hyovis).
The full stack routes brightness + on/off commands from a Raspberry Pi 4 backend → LoRa transmitter → LoRa receiver Arduino → I²C slave Arduino → AC dimmer module → Actual AC street light.

This repo contains all the firmware + backend modules required to deploy a fully functional smart-lighting endpoint.

🏗️ System Architecture
Web Dashboard → Database → Raspberry Pi Backend (Python)
            ↓ Serial (UART)
        LoRa Transmitter (Master)
            ↓ LoRa RF
        LoRa Receiver (Arduino)
            ↓ I²C
      I²C Slave Arduino → Hyovis AC Dimmer → AC Street Light

🔹 Key Responsibilities
Module	Role
website/	Frontend UI for brightness + status control (1–100%)
python_backend.py	Fetches control values from DB and pushes to LoRa TX over serial
lora_transmitter.ino	Sends (status,brightness) over LoRa
lora_reciver.ino	Receives packet → forwards to I²C slave
i2cslave.ino	Drives AC dimmer via PWM/phase-cut control
Hyovis AC Dimmer Module	Handles actual mains-controlled light dimming
💡 Features

Long-range LoRa communication (433MHz)

Real-time remote brightness control (1–100%)

Remote ON/OFF switching

AC phase-cut dimming using Hyovis MCU Dimmer Module

Raspberry Pi backend fetches DB settings dynamically

Fully modular architecture → plug-and-scale for multiple street lights

Fault-resilient design with change-detection to avoid redundant I²C traffic

📂 Repository Structure
Smart-Street-Light/
│── website/                 # Web UI (dashboard)
│── i2cslave.ino             # AC Dimmer + I²C receiver
│── lora reciver.ino         # LoRa RX → I²C master
│── lora transmitter.ino     # LoRa TX → Pi serial interface
│── python_backend.py        # Pi-side server pulling DB values
│── LICENSE
│── README.md                # You're reading this

🧠 Technical Workflow
1. Web App → Database

User sets brightness + ON/OFF for a street light.

2. Raspberry Pi Backend

python_backend.py polls the database and sends values via serial to the LoRa transmitter.

3. LoRa Transmitter → LoRa Receiver

Transmitter formats data as:

status,brightness


Receiver parses and verifies the data packet.

4. LoRa RX → I²C Slave Arduino

Receiver forwards data only if changed to reduce bus noise.

5. I²C Slave Arduino → AC Dimmer

Converts brightness (0–100) → PWM (0–255)

Writes PWM to Hyovis AC Dimmer module

Dimmer performs phase-angle cutting on 100–230V AC

Controls lamp intensity smoothly

⚡ Hardware Used

Raspberry Pi 4 (4GB/8GB)

LoRa SX1278 modules (433 MHz)

Arduino Nano / Uno

Hyovis AC Dimmer Module (MCU version)

AC Street Light (100–230V)

I²C wiring (SDA/SCL)

UART TX/RX between Pi and LoRa TX module

🔧 Setup Instructions
1. Clone the repo
git clone https://github.com/Adk-157/Smart-Street-Light.git
cd Smart-Street-Light

2. Flash LoRa Transmitter firmware

Upload lora transmitter.ino to the Arduino connected to your Raspberry Pi.

3. Flash LoRa Receiver firmware

Upload lora reciver.ino to the Arduino connected to the dimmer node.

4. Flash I²C Slave firmware

Upload i2cslave.ino to the dimmer-controller Arduino.

5. Run backend
python3 python_backend.py

6. Launch frontend

Run website folder with any server or deploy to your hosting.

🔐 Safety Notice

This project interfaces with high-voltage AC mains.
Do NOT handle live wiring without proper insulation, tools, and experience.
Hyovis module isolates microcontroller circuitry — but treat AC with respect.

🧩 Future Improvements

Multi-node LoRa mesh support

Cloud-based control panel

Predictive dimming using traffic flow ML models

Real-time power monitoring (ZMQ current sensor)

OTA updates for field nodes

🏁 Status

✔️ Prototype complete
✔️ Fully tested on AC lighting
✔️ Scalable to multiple street lights
✔️ Backend + hardware stable