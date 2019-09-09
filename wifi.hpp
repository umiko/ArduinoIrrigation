#include <Arduino.h>
#include <WiFiNINA.h>

class wifi
{
private:
  WiFiClass connection = WiFi;
  boolean checkModuleAvailability();

public:
  void establishConnection(const char ssid[], const char pass[], bool retry);
  void printConnectionProperties();
  WiFiClass getConnection();
  void setHostname(char hostname[]);
};