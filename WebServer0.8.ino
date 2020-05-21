#include "Coffee.h"
#include "SoftwareSerial.h"

#include <Servo.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

#define BUFFER_SIZE 8
#define TFT_DC 9
#define TFT_CS 10

//Setting up coordinates for LCD
#define FRAME_X 0
#define FRAME_Y 0
#define FRAME_W 320
#define FRAME_H 240

#define BUT_W 125
#define BUT_H 50

#define AME_X 30
#define AME_Y 60
#define LAT_X 30
#define LAT_Y 120

#define SENS_X 165
#define SENS_Y 60

#define TEMP_X 165
#define TEMP_Y 120


// Emulate Serial1 on pins 18/19 if not present
#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(18, 19); // RX, TX
#endif


void HTTP_Response(WiFiEspClient);
void printWifiStatus();

boolean Ame = false;
boolean Lat = false;

const int EMPTY = 50;

//Pins for motors
const int MILK_M = 26;
const int WATER_M = 27;
const int GRINDER_M = 28;

//Creating objects for sensors and motors
Servo disp;
Motor milk(MILK_M);
Motor water(WATER_M);
Motor grind(GRINDER_M);
LM35 t1;
US_Sensor u1;
Level_Sensor l1;
Adafruit_FT6206 ts = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//char ssid[] = "Redmi";
//char pass[] = "580b6ba6049b";
//char ssid[] = "Xperia E4_419c";                  // your network 1 SSID (name)
//char pass[] = "abcd1234";                        // your network 1 password
char ssid[] = "Pretty Fly for a WiFi";             // your network 2 SSID (name)
char pass[] = "GetOffYourPhone1";                  // your network 2 password
int status = WL_IDLE_STATUS;                       // the Wifi radio's status
int reqCount = 0;                                  // number of requests received

RingBuffer buf(BUFFER_SIZE);
WiFiEspServer server(80);

void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);

  }

  Serial.println(F("You're connected to the network"));
  printWifiStatus();

  // start the web server on port 80
  server.begin();

  tft.begin();

  if (!ts.begin(40)) {
    Serial.println("Unable to start touchscreen.");
  }
  else {
    Serial.println("Touchscreen started.");
  }
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  AmeBtn();
  LatBtn();
  disp.attach(44);
}

void loop() {
  int choice = 0;

  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    p.x = map(p.x, 0, 240, 240, 0);
    p.y = map(p.y, 0, 320, 320, 0);
    int y = tft.height() - p.x;
    int x = p.y;

    if ((x > AME_X) && (x < (AME_X + BUT_W))) {
      if ((y > AME_Y) && (y < (AME_Y + BUT_H))) {
        choice = 1;
      }
    }
    if ((x > LAT_X) && (x < (LAT_X + BUT_W))) {
      if ((y > LAT_Y) && (y < (LAT_Y + BUT_H))) {
        choice = 2;
      }
    }
  }

  WiFiEspClient client = server.available();
  if (client) {
    Serial.println(F("New client"));
    buf.init();

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        buf.push(c);

        if (buf.endsWith("\r\n\r\n")) {
          HTTP_Response(client);
          break;
        }
        if (buf.endsWith("GET /1")) {
          choice = 1;
        }
        else if (buf.endsWith("GET /2")) {
          choice = 2;
        }
        else if (buf.endsWith("GET /3")) {
          choice = 3;
        }
        else if (buf.endsWith("GET /4")) {
          choice = 4;
        }
      }
    }
    client.stop();
    Serial.println(F("Client disconnected"));
  }
  if (u1.perc(EMPTY) && l1.milk_empty()) {
    switch (choice) {
      case 1:
        Serial.println(choice);
        grind.motor_start(HIGH);
        delay(2000);
        grind.motor_start(LOW);
        disp.write(190);
        delay(2000);
        disp.write(10);
        water.motor_start(HIGH);
        delay(2000);
        water.motor_start(LOW);
        choice = 0;
        break;

      case 2:
        Serial.println(choice);
        grind.motor_start(HIGH);
        delay(2000);
        grind.motor_start(LOW);
        disp.write(190);
        delay(2000);
        disp.write(10);
        water.motor_start(HIGH);
        milk.motor_start(HIGH);
        delay(2000);
        water.motor_start(LOW);
        milk.motor_start(LOW);
        choice = 0;
        break;
    }
  }
}
