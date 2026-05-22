# Fully Autonomous ESP32 Robotic Vehicle

## Description
This project is a firmware implementation for an autonomous 4-wheel drive (4WD) robotic vehicle. Powered by an ESP32 microcontroller and dual L298N motor drivers, the robot uses 5 ultrasonic sensors (front-left, front-center, front-right, left, right) to intelligently navigate and avoid obstacles in its path.

## Hardware Requirements
- ESP32 Development Board
- 2x L298N Motor Driver Modules
- 4x DC Motors
- 5x HC-SR04 Ultrasonic Sensors
- Power Source (Battery Pack)
- Chassis and Wheels

## Pin Configuration

### Ultrasonic Sensors
- Front-Left: TRIG = 25, ECHO = 33
- Front-Center: TRIG = 32, ECHO = 35
- Front-Right: TRIG = 14, ECHO = 34
- Right: TRIG = 21, ECHO = 36
- Left: TRIG = 16, ECHO = 17

### Rear Motors
- ENA: 4
- ENB: 5
- IN1: 15
- IN2: 2
- IN3: 13
- IN4: 12

### Front Motors
- ENA: 23
- ENB: 22
- IN1: 27
- IN2: 26
- IN3: 18
- IN4: 19

## Software Requirements
- PlatformIO or Arduino IDE
- ESP32 Board Package

## Installation & Flashing
1. Clone the repository.
2. Open the project in PlatformIO or Arduino IDE.
3. Build and upload the firmware to your ESP32.
4. Once powered on, the robot will automatically begin navigating its environment.
