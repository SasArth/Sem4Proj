// Basic demo for accelerometer readings from Adafruit MPU6050

#include <ESP8266WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
//#include "ESP_MICRO.h"
#include "ThingSpeak.h"


Adafruit_MPU6050 mpu;

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

const char* ssid = "xxxxxx";
const char* password = "yyyyyy";

WiFiClient  client;

unsigned long myChannelNumber1 = 1;
unsigned long myChannelNumber2 = 2;
unsigned long myChannelNumber3 = 3;
const char * myWriteAPIKey = "XXXXXXXZZZZZZZZYYYYYYY";

float Throttle = 0.00;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;

void setup(void) {
  Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
//start("SAS","atharvass");
WiFi.status();
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
}


void loop() {
   if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(1000);     
      } 
      Serial.println("\nConnected.");
    }


  Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);

AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);

int Xaxis, Yaxis, Throttle;
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
/*Serial.print("\nAngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
 
Serial.print("AngleZ= ");
Serial.println(z);*/
Serial.println("-----------------------------------------");

if((x-10)*(x-60) <= 0){Serial.print("\nUpArrow");Yaxis = 0;}
else if((x-300)*(x-350) <= 0){Serial.print("\nDownArrow");Yaxis=1;}
else{Serial.print("\nAleioronsZero");Yaxis=2;}

if((y-15)*(y-60) <= 0){Serial.print("\nRightArrow");Xaxis=0;}
else if((y-300)*(y-350) <= 0){Serial.print("\nLeftArrow");Xaxis=1;}
else{Serial.print("\nElevatorZero");Xaxis=2;}
Serial.println("\n-----------------------------------------");
Throttle = 10;
int j = ThingSpeak.writeField(myChannelNumber1, 1, Xaxis, myWriteAPIKey);
int k = ThingSpeak.writeField(myChannelNumber2, 1, Yaxis, myWriteAPIKey);
int l = ThingSpeak.writeField(myChannelNumber3, 1, Throttle, myWriteAPIKey);

if(j == 200 && k==200 && l==200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(j));
    }

delay(200);
}
