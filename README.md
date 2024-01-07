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

<img src="https://i.ibb.co/DLdqB0G/Whats-App-Image-2024-01-03-at-19-38-20.jpg" alt="Whats-App-Image-2024-01-03-at-19-38-20" border="0">

## Web Interface Controls
# R/C FIRE FIGHTING BOT Controls

<iframe srcdoc='
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <style>
    .arrows {
      font-size: 42px;
      color: #50c3ff;
    }
    td.button {
      background-color: #7c7c7c;
      border-radius: 25%;
      box-shadow: 0px 0px 2px 1.5px #45c8ff;
    }
    td.button:active {
      transform: translate(2px, 2px);
      box-shadow: none;
    }
    html {
      height: 100%;
      width: 100%;
    }
    .noselect {
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -khtml-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      background-color: #494949;
      width: 100%;
      height: 92vh;
      margin: 0;
      padding: 0;
    }
    .slidecontainer {
      width: 100%;
    }
    .slider {
      -webkit-appearance: none;
      width: 100%;
      height: 20px;
      border-radius: 5px;
      background: #999999;
      outline: none;
      opacity: 0.7;
      -webkit-transition: .2s;
      transition: opacity .2s;
    }
    .slider:hover {
      opacity: 1;
    }
    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 10vmin;
      height: 10vmin;
      border-radius: 30%;
      background: #c9ff90;
      cursor: pointer;
    }
    .slider::-moz-range-thumb {
      width: 20%;
      height: 20%;
      border-radius: 50%;
      background: red;
      cursor: pointer;
    }
    @font-face {
      font-family: 'Orbitron';
      font-style: normal;
      font-weight: 400;
      src: url(https://fonts.gstatic.com/s/orbitron/v31/yMJMMIlzdpvBhQQL_SC3X9yhF25-T1nyGy6BoWgz.woff2) format('woff2');
      unicode-range: U+0000-00FF, U+0131, U+0152-0153, U+02BB-02BC, U+02C6, U+02DA, U+02DC, U+0304, U+0308, U+0329, U+2000-206F, U+2074, U+20AC, U+2122, U+2191, U+2193, U+2212, U+2215, U+FEFF, U+FFFD;
    }
  </style>
</head>

<body class="noselect" align="center">
  <h1 style="color: rgb(255 205 75);text-align:center; margin: 8vh;font-family: cursive;">R/C FIRE FIGHTING BOT</h1>
  <h2 style="color: #d5ffa9;text-align:center;font-family: cursive;">Controls</h2>
  <table id="mainTable" style="width: 92%;margin:auto;table-layout:fixed;margin-top: 12vh;" CELLSPACING=10>
    <tr>
      <td></td>
      <td class="button" ontouchstart='sendButtonInput("MoveCar","1")' ontouchend='sendButtonInput("MoveCar","0")'><span
          class="arrows">&#8679;</span></td>
      <td></td>
    </tr>
    <tr>
      <td class="button" ontouchstart='sendButtonInput("MoveCar","3")' ontouchend='sendButtonInput("MoveCar","0")'><span
          class="arrows">&#8678;</span></td>
      <td class="button"></td>
      <td class="button" ontouchstart='sendButtonInput("MoveCar","4")' ontouchend='sendButtonInput("MoveCar","0")'><span
          class="arrows">&#8680;</span></td>
    </tr>
    <tr>
      <td></td>
      <td class="button" ontouchstart='sendButtonInput("MoveCar","2")' ontouchend='sendButtonInput("MoveCar","0")'><span
          class="arrows">&#8681;</span></td>
      <td></td>
    </tr>
    <tr />
    <tr />
    <tr />
    <tr />
    <tr />
    <tr />
    <tr>
      <td style="text-align:left;font-size:25px"><b style="color: #d5ffa9;font-family: cursive;">Speed:</b></td>
      <td colspan=2>
        <div class="slidecontainer">
          <input type="range" min="0" max="255" value="150" class="slider" id="Speed"
            oninput='sendButtonInput("Speed",value)'>
        </div>
      </td>
    </tr>
    <tr>
      <td style="text-align:left;font-size:25px"><b style="color: #d5ffa9;font-family: cursive;">Servo Angle:</b></td>
      <td colspan=2>
        <div class="slidecontainer">
          <input type="range" min="0" max="180" value="90" class="slider" id="ServoAngle"
            oninput='sendButtonInput("ServoAngle",value)'>
        </div>
      </td>
    </tr>
    <tr>
      <td style="text-align:left;font-size:25px"><b style="color: #d5ffa9;font-family: cursive;">Pump State:</b></td>
      <td colspan=2>
        <div class="slidecontainer">
          <input type="range" min="0" max="1" value="0" class="slider" id="RelayState"
            oninput='sendButtonInput("RelayState",this.value)'>
        </div>
      </td>
    </tr>
  </table>
</body>
</html>' width="600" height="800" style="border:none;"></iframe>

- **Arrow Buttons**: Move the robot in different directions.
- **Speed Slider**: Adjust the speed of the motors.
- **Servo Angle Slider**: Control the angle of the servo.
- **Pump State Slider**: Activate or deactivate the water pump.

## Contributing

Feel free to contribute to this project by creating issues or pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

