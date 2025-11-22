🏙️ Smart Street Light – Remote LoRa-Based AC Dimming System

A scalable, long-range, edge-driven street-lighting control stack featuring LoRa communication and AC phase-cut dimming.

🚀 Overview

This project implements a remote-controlled smart street-light system powered by LoRa, I²C, and an AC dimmer module (Hyovis). The system provides long-range control over brightness and status, managed centrally via a web dashboard and a Raspberry Pi backend.

The full stack routes control commands through a series of microcontrollers and communication protocols:

Web Dashboard → Database

Raspberry Pi Backend (Python) → LoRa Transmitter (via Serial)

LoRa Transmitter → LoRa Receiver (via RF)

LoRa Receiver → I²C Slave Arduino (via I²C)

I²C Slave Arduino → Hyovis AC Dimmer Module → Actual AC Street Light

🏗️ System Architecture

The modular architecture ensures scalability and clear separation of concerns:

Module

Role

website/Frontend

UI for brightness + status control (1–100%)

python_backend.py

Fetches control values from DB and pushes to LoRa TX over serial

lora_transmitter.ino

Sends (status, brightness) over LoRa RF

lora_reciver.ino

Receives packet $\rightarrow$ forwards to I²C slave

i2cslave.ino

Drives AC dimmer via PWM/phase-cut control

Hyovis AC Dimmer Module

Handles actual mains-controlled light dimming (100–230V AC)

💡 Features

Long-Range Communication: Utilizes LoRa SX1278 (433MHz) for extended coverage, ideal for scattered street light infrastructure.

Real-Time Control: Remote brightness adjustment (1–100%) and ON/OFF switching.

Reliable Dimming: Implements AC phase-cut dimming using the Hyovis MCU Dimmer Module for smooth intensity control.

Scalable Backend: Raspberry Pi dynamically fetches settings, supporting easy expansion to manage multiple light nodes.

Fault Resilience: Uses change-detection logic on the LoRa Receiver to minimize redundant I²C bus traffic and system load.

🧠 Technical Workflow

Web App $\rightarrow$ Database: User interacts with the web interface to set the desired brightness and state for a specific street light node, which is stored in a database (e.g., Firebase, PostgreSQL).

Raspberry Pi Backend: python_backend.py continuously polls the database for changes and formats the control values (status,brightness) before sending them via UART serial to the LoRa transmitter Arduino.

LoRa Transmitter $\rightarrow$ LoRa Receiver: The transmitter sends the formatted data packet over the long-range RF link.

LoRa RX $\rightarrow$ I²C Slave Arduino: The receiver parses the packet and, only if the command is different from the previous state, forwards the new status and brightness values to the I²C Slave Arduino.

I²C Slave Arduino $\rightarrow$ AC Dimmer:

The I²C Slave converts the brightness percentage (0–100) into a compatible PWM value (0–255).

It writes this PWM value to the Hyovis AC Dimmer module's control pin.

The Dimmer module then performs phase-angle cutting on the 100–230V AC line to smoothly control the lamp intensity.

⚡ Hardware Used

Controller: Raspberry Pi 4 (4GB/8GB)

RF: LoRa SX1278 modules (433 MHz)

Microcontrollers: Arduino Nano / Uno (one for LoRa RX/I²C Master, one for I²C Slave/Dimmer control)

Power Control: Hyovis AC Dimmer Module (MCU version)

Load: AC Street Light (100–230V)

Interfacing: I²C wiring (SDA/SCL) and UART TX/RX between Pi and LoRa TX module.

📂 Repository Structure

Smart-Street-Light/
│── website/                 # Web UI (dashboard)
│── i2cslave.ino             # AC Dimmer + I²C receiver firmware
│── lora reciver.ino         # LoRa RX → I²C master firmware
│── lora transmitter.ino     # LoRa TX → Pi serial interface firmware
│── python_backend.py        # Pi-side server pulling DB values
│── LICENSE
│── README.md


🔧 Setup Instructions

1. Clone the repo

git clone [https://github.com/Adk-157/Smart-Street-Light.git](https://github.com/Adk-157/Smart-Street-Light.git)
cd Smart-Street-Light


2. Flash Firmware

Use the Arduino IDE to flash the following firmwares:

LoRa Transmitter: Upload lora transmitter.ino to the Arduino connected to your Raspberry Pi.

LoRa Receiver: Upload lora reciver.ino to the Arduino connected to the dimmer node.

I²C Slave: Upload i2cslave.ino to the dimmer-controller Arduino.

3. Run Backend

Ensure your database configuration is correct in python_backend.py.

python3 python_backend.py


4. Launch Frontend

Serve the website folder using a local server or deploy it to your chosen hosting service.

🔐 Safety Notice

This project interfaces with high-voltage AC mains (100–230V).

Do NOT handle live wiring without proper insulation, tools, and professional experience.

Ensure all high-voltage connections are secure and properly insulated.

The Hyovis module provides isolation for the microcontroller circuitry—but always treat the AC side with extreme caution and respect.

🧩 Future Improvements

Implement multi-node LoRa mesh support for dynamic routing.

Develop a full cloud-based control panel (e.g., using AWS IoT or Google Cloud IoT).

Integrate predictive dimming using real-time traffic flow ML models.

Add real-time power monitoring using ZMQ current sensors.

Enable Over-The-Air (OTA) updates for field nodes.

🏁 Status

Component

Status

Prototype

✔️ Complete

AC Dimming

✔️ Fully tested on AC lighting

Scalability

✔️ Scalable to multiple street lights

Backend/Hardware

✔️ Stable
