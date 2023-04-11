#include <Wire.h>
#include "ESP_MICRO.h"
#include <ESP8266WiFi.h>

int port = 5055;
WiFiServer server(port);

const char *ssid = "SAS";
const char *password = "atharvass";

void setup() {
  // put your setup code here, to run once:

WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

Serial.println("Connecting to Wifi");
while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
delay(500);  
}
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);

Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
server.begein();
Serial.print("Open Telnet and connect to IP:");
Serial.print(WiFi.localIP());
Serial.print("on port ");
Serial.println(port);
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();

  if (client){
    if(client.connected()){
      Serial.println("Client Connected");
    }
    while(client.connected()){
      while(client.available()>0){
        Serial.write(client.read());
      }
    }
    client.stop();
    Serial.println("Client dis");
  }

}
