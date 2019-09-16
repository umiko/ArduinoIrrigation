#include <Arduino.h>
#include <ArduinoJson.h>

#include <moistureMeter.hpp>
#include <pump.hpp>
#include <flowrate.hpp>

#include "arduino_secrets.h" //this includes defintions of the WiFi SSID and password and has to be done by the user
#include "wifi.hpp"

wifi wireless;
WiFiClient client;
moistureMeter mm;
pump p;
moistureMeasurement measurement;

void setup()
{
  //Serial
  Serial.begin(9600);
  while (!Serial)
  {
  }
  //wifi connection
  wireless = wifi();
  wireless.establishConnection(SECRET_SSID, SECRET_PASS, true);
  wireless.printConnectionProperties();
  //moisture sensor
  mm = moistureMeter(2, A7, 840);
  mm.printConfig();
  //pump
  p = pump(1.2, _minute, 3, false);
  p.printConfig();
  //TODO: set up wificlient
}

void loop()
{
  measurement = mm.measureMoisture();
  measurement.print();
  //TODO: use JSON library and send measurements to the server

  // set measurement interval including measuring duration
  delay(600000-(SAMPLE_SIZE*20));
}
