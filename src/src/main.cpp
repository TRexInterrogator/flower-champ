#include <Arduino.h>
#include "env.h"



#define SENSOR_01 33
#define SENSOR_02 32
#define MAX_DRY 4095
#define MAX_WET 2330
#define IS_DRY 4090


int moisture_01 = 0;
int moisture_02 = 0;




void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_01, INPUT);
    pinMode(SENSOR_02, INPUT);

    Serial.println("");
    Serial.println("WiFi credentials:");
    Serial.println(ENV::SSID);
    Serial.println(ENV::WiFiPwd);
}


void loop() {   
    moisture_01 = analogRead(SENSOR_01);
    moisture_02 = analogRead(SENSOR_02);

    String output = "Sensor 01: ";
    output.concat(String(moisture_01));
    output.concat(" Sensor 02: ");
    output.concat(String(moisture_02));
    Serial.println(output);
    
    delay(2000);
}