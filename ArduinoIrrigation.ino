#include <Arduino.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" //this includes defintions of the WiFi SSID and password and has to be done by the user
#include "wifi.hpp"
#include <moistureMeter.hpp>

int wifi_status = WL_IDLE_STATUS;
wifi wireless = wifi();
moistureMeter mm = moistureMeter(2, A0, 0);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }
  wireless.establishConnection(SECRET_SSID, SECRET_PASS, true);
  wireless.printConnectionProperties();
  mm.printConfig();
}

void loop()
{
  mm.measureMoisture().print();
  delay(10000);
}
