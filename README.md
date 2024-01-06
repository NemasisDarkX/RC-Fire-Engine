# R/C Fire Fighting Bot

![Project Image](images/project_image.jpg)

## Overview

This project implements a remote-controlled fire-fighting robot using an ESP32 microcontroller. The robot can be controlled via a web interface, allowing users to maneuver the robot, adjust speed, control a servo, and activate a water pump.

## Features

- Remote control using a web interface
- Speed control for the motors
- Servo angle adjustment
- Water pump activation

## Hardware Components

- ESP32 microcontroller
- DC Motors and Motor Drivers
- Servo Motor
- Relay for Water Pump
- Chassis and Wheels
- Power Supply

![Inside Image](images/inside_image.jpg)

## Getting Started

### Prerequisites

- Arduino IDE: https://www.arduino.cc/en/software
- ESP32 Driver: Install from https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
- [ESPAsyncWebServer Library](https://github.com/me-no-dev/ESPAsyncWebServer.git)
- Other libraries: install other libraries from the IDE's Librarys

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/fire-fighting-bot.git
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

![Outside Image](images/outside_image.jpg)

## Web Interface Controls

- **Arrow Buttons**: Move the robot in different directions.
- **Speed Slider**: Adjust the speed of the motors.
- **Servo Angle Slider**: Control the angle of the servo.
- **Pump State Slider**: Activate or deactivate the water pump.

## Contributing

Feel free to contribute to this project by creating issues or pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

