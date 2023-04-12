#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

const int NVE = 13;
const int PVE = 15;
int PVES = 0;
int NVES = 0;

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

if((x-10)*(x-60) <= 0){Serial.print("\nUpArrow");}
else if((x-300)*(x-350) <= 0){Serial.print("\nDownArrow");}
else{Serial.print("\nAleioronsZero");}

if((y-15)*(y-60) <= 0){Serial.print("\nRightArrow");}
else if((y-300)*(y-350) <= 0){Serial.print("\nLeftArrow");}
else{Serial.print("\nElevatorZero");}


if(PVES == HIGH){Serial.print("\n+ve Throt");}

if(NVES == LOW){Serial.print("\n-ve Throt");}


Serial.println("\n-----------------------------------------");






delay(1000);

}
