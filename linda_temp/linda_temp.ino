#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
}

HTTPClient httpClient;

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("SSID", "KEY");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


float getTemp() {
  float val =  system_adc_read();
  float temp = val * 100 / 1024;
  return temp;
}


void loop() {

  Serial.println(getTemp());
  char tuplef[] = "tuple={\"type\":\"sensor\",\"where\":\"myroom\",\"name\":\"temperature\",\"value\":\"";
  char tupleb[] = "\"}";
  String ts = String(tuplef) + String(getTemp()) + String(tupleb);

  Serial.println(ts);
  httpClient.begin("********.com");
  httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = httpClient.POST(ts);
  httpClient.writeToStream(&Serial);
  httpClient.end();
  Serial.println(httpCode);
  delay(5000);
}
