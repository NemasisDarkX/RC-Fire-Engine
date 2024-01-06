#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <sstream>

struct MOTOR_PINS
{
  int pinEn;
  int pinIN1;
  int pinIN2;
};

struct SERVO_RELAY_PINS
{
  int pinServo;
  int pinRelay;
};

std::vector<MOTOR_PINS> motorPins =
{
  {13, 14, 12},  //RIGHT_MOTOR Pins (EnA, IN1, IN2)
  {21, 5, 18},  //LEFT_MOTOR  Pins (EnB, IN3, IN4)
};

SERVO_RELAY_PINS servoRelayPins = {22, 23};  

#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 3
#define STOP 0

#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1

#define FORWARD 1
#define BACKWARD -1

const int PWMFreq = 1000; 
const int PWMResolution = 8;
const int PWMSpeedChannel = 4;

Servo myservo;

const char* ssid     = "Fire Engine";
const char* password = "12345678910";

AsyncWebServer server(80);
AsyncWebSocket wsCarInput("/CarInput");

const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
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
              <td class="button" ontouchstart='sendButtonInput("MoveCar","1")'
                  ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8679;</span></td>
              <td></td>
          </tr>
          <tr>
              <td class="button" ontouchstart='sendButtonInput("MoveCar","3")'
                  ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8678;</span></td>
              <td class="button"></td>
              <td class="button" ontouchstart='sendButtonInput("MoveCar","4")'
                  ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8680;</span></td>
          </tr>
          <tr>
              <td></td>
              <td class="button" ontouchstart='sendButtonInput("MoveCar","2")'
                  ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">&#8681;</span></td>
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
      <script>
          var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + "/CarInput";
          var websocketCarInput;
          function initCarInputWebSocket() {
              websocketCarInput = new WebSocket(webSocketCarInputUrl);
              websocketCarInput.onopen = function (event) {
                  var speedButton = document.getElementById("Speed");
                  sendButtonInput("Speed", speedButton.value);

                  var servoAngle = document.getElementById("ServoAngle");
                  sendButtonInput("ServoAngle", servoAngle.value);

                  var relayState = document.getElementById("RelayState");
                  sendButtonInput("RelayState", relayState.value);
              };
              websocketCarInput.onclose = function (event) { setTimeout(initCarInputWebSocket, 2000); };
              websocketCarInput.onmessage = function (event) { };
          }
          function sendButtonInput(key, value) {
              var data = key + "," + value;
              websocketCarInput.send(data);
          }
          window.onload = initCarInputWebSocket;
          document.getElementById("mainTable").addEventListener("touchend", function (event) {
              event.preventDefault()
          });
      </script>
  </body>
</html>
)HTMLHOMEPAGE";


void rotateMotor(int motorNumber, int motorDirection)
{
  if (motorDirection == FORWARD)
  {
    digitalWrite(motorPins[motorNumber].pinIN1, HIGH);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);
  }
  else if (motorDirection == BACKWARD)
  {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, HIGH);
  }
  else
  {
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);
  }
}

void moveCar(int inputValue)
{
  Serial.printf("Got value as %d\n", inputValue);
  rotateMotor(RIGHT_MOTOR, STOP);
  rotateMotor(LEFT_MOTOR, STOP);

  switch (inputValue)
  {

    case UP:
      rotateMotor(RIGHT_MOTOR, FORWARD);
      rotateMotor(LEFT_MOTOR, FORWARD);
      break;

    case DOWN:
      rotateMotor(RIGHT_MOTOR, BACKWARD);
      rotateMotor(LEFT_MOTOR, BACKWARD);
      break;

    case LEFT:
      rotateMotor(RIGHT_MOTOR, FORWARD);
      rotateMotor(LEFT_MOTOR, BACKWARD);
      break;

    case RIGHT:
      rotateMotor(RIGHT_MOTOR, BACKWARD);
      rotateMotor(LEFT_MOTOR, FORWARD);
      break;

    case STOP:
      rotateMotor(RIGHT_MOTOR, STOP);
      rotateMotor(LEFT_MOTOR, STOP);
      break;

    default:
      rotateMotor(RIGHT_MOTOR, STOP);
      rotateMotor(LEFT_MOTOR, STOP);
      break;
  }
}

void controlServo(int angle)
{
  angle = constrain(angle, 0, 180);
  myservo.write(angle);
}

void controlRelay(bool state)
{
  digitalWrite(servoRelayPins.pinRelay, state ? HIGH : LOW);
}

void handleRoot(AsyncWebServerRequest *request)
{
  request->send_P(200, "text/html", htmlHomePage);
}

void handleNotFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "File Not Found");
}

void onCarInputWebSocketEvent(AsyncWebSocket *server,
  AsyncWebSocketClient *client,
  AwsEventType type,
  void *arg,
  uint8_t *data,
  size_t len)
{
  switch (type)
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      moveCar(STOP);
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
      {
        std::string myData = "";
        myData.assign((char *)data, len);
        std::istringstream ss(myData);
        std::string key, value;
        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        Serial.printf("Key [%s] Value[%s]\n", key.c_str(), value.c_str());
        int valueInt = atoi(value.c_str());
        if (key == "MoveCar")
        {
          moveCar(valueInt);
        }
        else if (key == "Speed")
        {
          ledcWrite(PWMSpeedChannel, valueInt);
        }
        else if (key == "ServoAngle")
        {
          controlServo(valueInt);
        }
        else if (key == "RelayState")
        {
          controlRelay(valueInt != 0);
        }
      }
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;
  }
}

void setUpPinModes()
{
  
  ledcSetup(PWMSpeedChannel, PWMFreq, PWMResolution);

  for (int i = 0; i < motorPins.size(); i++)
  {
    pinMode(motorPins[i].pinEn, OUTPUT);
    pinMode(motorPins[i].pinIN1, OUTPUT);
    pinMode(motorPins[i].pinIN2, OUTPUT);

    
    ledcAttachPin(motorPins[i].pinEn, PWMSpeedChannel);
  }

  
  myservo.attach(servoRelayPins.pinServo);


  pinMode(servoRelayPins.pinRelay, OUTPUT);
  controlRelay(false);  

  moveCar(STOP);
}

void setup(void)
{
  setUpPinModes();
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);

  wsCarInput.onEvent(onCarInputWebSocketEvent);
  server.addHandler(&wsCarInput);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  wsCarInput.cleanupClients();
}
