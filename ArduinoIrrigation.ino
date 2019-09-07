#include "arduino_secrets.h" //this includes defintions of the WiFi SSID and password and has to be done by the user
#include <Arduino.h>
#include <WiFiNINA.h>

int wifi_status = WL_IDLE_STATUS;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  Serial.println("Serial connection established!");

  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("WiFi Module Communication failed");
    while (true)
    {
    }
  }

  while (wifi_status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to \"");
    Serial.print(SECRET_SSID);
    Serial.println("\"...");
    // Connect to WPA/WPA2 network:
    wifi_status = WiFi.begin(SECRET_SSID, SECRET_PASS);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Connection established!");
}

void loop()
{
}
