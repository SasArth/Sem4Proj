#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include "ESP_MICRO.h"

const int NVE = 13;
const int PVE = 15;
int PVES = 0;
int NVES = 0;
int p;
int r;
int t;

Adafruit_MPU6050 mpu;

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;


void setup() {
  // put your setup code here, to run once:
  start("MGRECP-ACCTLAP 8985","f0856&M3");
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);

pinMode(PVE, INPUT);
pinMode(NVE, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
waitUntilNewReq();
PVES = 0;
NVES = 0;

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
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

PVES = digitalRead(PVE);
NVES = digitalRead(NVE);

Serial.println("-----------------------------------------");

if((x-10)*(x-60) <= 0){Serial.print("\nUpArrow");p = 2;}
else if((x-300)*(x-350) <= 0){Serial.print("\nDownArrow");p = 8;}
else{Serial.print("\nAleioronsZero");p = 5;}

if((y-15)*(y-60) <= 0){Serial.print("\nRightArrow");r = 4;}
else if((y-300)*(y-350) <= 0){Serial.print("\nLeftArrow");r = 6;}
else{Serial.print("\nElevatorZero");r = 5;}


if(PVES == HIGH){Serial.print("\n+ve Throt");t = 7;}

else if(NVES == HIGH){Serial.print("\n-ve Throt");t = 1;}

else{Serial.print("\nZero Throt");t = 9;}

//Serial.print(p + r + t);


Serial.println("\n-----------------------------------------");

//returnThisInt(p);
returnThisInt(concat(p, r, t));
//returnThisInt(r);
//returnThisInt(t);

delay(1000);

}

int concat(int x, int y, int z)
{
  
    char s1[20];
    char s2[20];
    char s3[20];
    
  
    // Convert both the integers to string
    sprintf(s1, "%d", x);
    sprintf(s2, "%d", y);
    sprintf(s3, "%d", z);
  
    // Concatenate both strings
    strcat(s1, s2);
    strcat(s1, s3);
  
    // Convert the concatenated string
    // to integer
    int c = atoi(s1);
   
    return c;}
