/*
  Titre      : Titre du programme
  Auteur     : Cedric Yonta
  Date       : 12/04/2022
  Description: Une description du programme
  Version    : 0.0.1
*/



#include <Arduino.h>
//Libraries
#include <Keypad.h>
#include <Wire.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnectoR.h"

#define I2C_SLAVE_LED_ADDRESS  9
//Constants
#define ROWS 4
#define COLS 4

int ledPin = 10 ;
int x  ;
//Parameters
const char kp4x4Keys[ROWS][COLS]  = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowKp4x4Pin [4] = {9, 8, 7, 6};
byte colKp4x4Pin [4] = {5, 4, 3, 2};
//Variables
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS);


void setup() {
   wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();  
 //Init Serial USB
 Serial.begin(9600);
 Serial.println(F("Initialize System"));

 Wire.begin();
}
void loop() {
 char customKey = kp4x4.getKey();
 if (customKey) {
   Serial.println(customKey);
  
   if (customKey == 'A')
 {
   x = 180;
 }
 else if (customKey == 'B')
 {
   x = 1 ;
 }

 else if (customKey == 'C')
 {
   x = -1 ;
 }else if (customKey == 'D')
 {
   x = 0 ;
 }
 else
 {
   /* code */
 }
 
 
  Serial.println(x);
  appendPayload("Servo_Position", x);
  sendPayload();    }
   
 }

 
 
  

  Wire.beginTransmission(I2C_SLAVE_LED_ADDRESS); // transmit to device #9
  
  Wire.write(x);              // sends x 
  Wire.endTransmission();    // stop transmitting

 
}
 
