//AUTHOR:
//umiko(https://github.com/umiko)
//Permission to copy and modify is granted under the MIT license
//
//DESCRIPTION:
//Main file for the irrigation System

#include <Arduino.h>
#include <ArduinoJson.h>

#include <moistureMeter.hpp>
#include <pump.hpp>
#include <flowrate.hpp>

#include "arduino_secrets.h" //this includes defintions of the WiFi SSID and password and the POST secrets. All that has to be done by the user
#include "wifi.hpp"

wifi wireless;
WiFiClient client;

DynamicJsonDocument doc(1024);

moistureMeter mm;
pump p;
moistureMeasurement measurement;

//the moisture percentage threshold under which the pump will be toggled once
const float irrigation_threshold = 0.70;
//the amount of water in liters that the pump will be toggled for
const float irrigation_amount = 0.10;
//the time in milliseconds between measurements
const ulong irrigation_interval = 600000;

void setup()
{
  //Serial
  Serial.begin(9600);
  while (!Serial)
  {
  }
  //wifi connection
  Serial.println("##### WiFi #####");
  wireless = wifi();
  wireless.establishConnection(SECRET_SSID, SECRET_PASS, 5);
  wireless.printConnectionProperties();
  //moisture sensor
  Serial.println("##### Sensor #####");
  mm = moistureMeter(2, A7, 840);
  mm.printConfig();
  //pump
  Serial.println("##### Pump #####");
  p = pump(1.2, _minute, 3, false);
  p.printConfig();
}

void loop()
{
  measurement = mm.measureMoisture();
  measurement.print();

  doc["data"]["baseline"] = measurement.m_baseline;
  doc["data"]["rawValue"] = measurement.m_rawValue;
  doc["data"]["threshold"] = irrigation_threshold;

  if (measurement.getMoistureInPercentage() < irrigation_threshold)
  {
    Serial.println("Soil seems dry, irrigating...");
    p.amountToggle(irrigation_amount);
  }
  upload();
  // set measurement interval including measuring duration
  delay(irrigation_interval - (SAMPLE_SIZE * 20));
}

void post()
{
  //header
  client.print("POST ");
  client.print(SECRET_ROUTE);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(SECRET_SERVER);
  client.println("Connection: close");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(measureJson(doc));
  client.println();
  //data
  serializeJson(doc, client);
  Serial.println("POST complete!");
  client.stop();
}

void upload()
{
  if (client.connect(SECRET_SERVER, SECRET_PORT))
  {
    Serial.println("Connected to Server");
    post();
  }
  else
  {
    Serial.println("Connection to Server failed, troubleshooting...");
    if (!wireless.isConnected())
    {
      Serial.println("No wireless connection found.");
      wireless.establishConnection(SECRET_SSID, SECRET_PASS, 5);
    }
    else
    {
      Serial.println("Wireless connection is established, retrying");
    }
    upload();
  }
}