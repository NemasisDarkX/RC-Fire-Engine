# R/C Fire Fighting Bot

<img src="https://i.ibb.co/qFJ2Dx1/full-cover.png" alt="full-cover" border="0">

## Overview

This project implements a remote-controlled fire-fighting robot using an ESP32 microcontroller. The robot can be controlled via a web interface, allowing users to maneuver the robot, adjust speed, control a servo, and activate a water pump.

## Features

- Remote control using a web interface
- Speed control for the motors
- Servo angle adjustment
- Water pump activation

## Hardware Components

- ESP32 microcontroller
- DC Motors and Motor Drivers(L298N)
- Servo Motor
- Relay for Water Pump(Single Channel)
- Chassis and Wheels
- Power Supply(18650, 3.7v)
- Dot PCB
- Male/Female Pin Header

<img src="https://i.ibb.co/0jYM2c5/re-v10.png" alt="re-v10" border="0">

## Getting Started

### Prerequisites

- Arduino IDE: https://www.arduino.cc/en/software
- ESP32 Driver: Install from https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
- [ESPAsyncWebServer Library](https://github.com/me-no-dev/ESPAsyncWebServer.git)
- Other libraries: install other libraries from the IDE's Librarys

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/NemasisDarkX/RC-Fire-Engine.git
    ```

2. Install the required libraries:

    - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer.git)
    - Other libraries: ESP32Servo, Arduino_ESP32_OTA, ESPAsyncTCP, AsyncTCP, AsyncElegantOTA

    Install the libraries using the Arduino Library Manager.

3. Open the Arduino IDE and load the project.

4. Upload the code to the ESP32.

### Usage

1. Connect your ESP32 to power.

2. Connect to the ESP32 Wi-Fi network (e.g., SSID: Fire Engine, Password: 12345678910).

3. Open a web browser and navigate to the ESP32's IP address (e.g., http://192.168.4.1).

4. Control the robot using the interactive web interface.

## Web Interface Controls

| Control | Description | Action |
|---------|-------------|--------|
| &#8679; | Move Forward | [Button](#) |
| &#8678; | Move Left    | [Button](#) |
| &#8680; | Move Right   | [Button](#) |
| &#8681; | Move Backward| [Button](#) |
| Speed   | Adjust speed | [Slider](#) |
| Servo Angle | Adjust servo angle | [Slider](#) |
| Pump State | Control pump state | [Slider](#) |

- **Arrow Buttons**: Move the robot in different directions.
- **Speed Slider**: Adjust the speed of the motors.
- **Servo Angle Slider**: Control the angle of the servo.
- **Pump State Slider**: Activate or deactivate the water pump.

## Contributing
Feel free to contribute to this project by creating issues or pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

