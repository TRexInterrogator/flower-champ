#include <Arduino.h>
#include <WiFi.h>
#include "env.h"
#include "flowerData.h"

using namespace ENV;


#define SENSOR_01 33
#define SENSOR_02 32
#define MAX_DRY 4095
#define MAX_WET 2330
#define IS_DRY 4090
#define READ_INTERVAL 5000
#define POST_INTERVAL 360


int moisture_01 = 0;
int moisture_02 = 0;
unsigned int updates = 0;



void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_01, INPUT);
    pinMode(SENSOR_02, INPUT);

    Serial.println("");
    Serial.println("WiFi credentials:");
    Serial.println(ENVars::SSID);
    Serial.println(ENVars::WiFiPwd);

    WiFi.begin(ENVars::SSID, ENVars::WiFiPwd);
    Serial.println("WiFi connecting ..");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(".");
    }

    Serial.println("Connected to network. IPv4:");
    Serial.println(WiFi.localIP());
}


void loop() {   
    delay(READ_INTERVAL);

    moisture_01 = analogRead(SENSOR_01);
    moisture_02 = analogRead(SENSOR_02);
    Serial.println("Sensor 01: " + String(moisture_01) + " Sensor 02: " + String(moisture_02));

    if (updates < POST_INTERVAL) {
        updates++;
    }
    else {
        // Send data every 30 mins.
        updates = 0;

        if (WiFi.status() == WL_CONNECTED) {
            FLC::FlowerData data_01("Flower-Champ-Ficus", moisture_01);
            FLC::FlowerData data_02("Flower-Champ-Palme", moisture_02);

            data_01.Post();
            data_02.Post();

            Serial.println("Sensor data POST complete");
        }
    }    
}