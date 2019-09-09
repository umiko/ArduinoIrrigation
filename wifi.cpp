#include "wifi.hpp"

void wifi::establishConnection(const char ssid[], const char pass[], boolean retry)
{
  if (!checkModuleAvailability())
  {
    Serial.println("Communication with WiFi Module failed!");
  }

  Serial.print("Attempting to connect to \"");
  Serial.print(ssid);
  Serial.println("\"...");

  do
  {
    Serial.println("Establishing connection...");
    connection.begin(ssid, pass);
    delay(10000);
  } while (connection.status() != WL_CONNECTED && retry);

  Serial.println("Connection Established!");
};

boolean wifi::checkModuleAvailability()
{
  int status = connection.status();
  return !(status == WL_NO_MODULE || status == WL_NO_SHIELD);
}

WiFiClass wifi::getConnection()
{
  return connection;
}

void wifi::setHostname(char hostname[])
{
  connection.setHostname(hostname);
}

void wifi::printConnectionProperties()
{
  if (Serial)
  {
    byte mac[6] = {};
    connection.macAddress(mac);
    Serial.print("IP: ");
    Serial.println(connection.localIP());
    Serial.print("MAC: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);
  }
}