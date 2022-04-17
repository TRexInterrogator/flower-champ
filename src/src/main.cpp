#include <Arduino.h>
#include <WiFi.h>
#include "env.h"
#include "flowerData.h"
#include "tempData.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


using namespace ENV;


#define SENSOR_01 33
#define SENSOR_02 32
#define TEMP_SENSOR 12


int moisture_01 = 0;
int moisture_02 = 0;
float temperature = 0.0f;


DHT_Unified dht(TEMP_SENSOR, DHT11);


void setup() {
    Serial.println("");

    pinMode(SENSOR_01, INPUT);
    pinMode(SENSOR_02, INPUT);
    pinMode(TEMP_SENSOR, INPUT);

    Serial.begin(9600);
    dht.begin();
    
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
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    
    moisture_01 = analogRead(SENSOR_01);
    moisture_02 = analogRead(SENSOR_02);
    temperature = event.temperature;
    
    if (WiFi.status() == WL_CONNECTED) {

        if (ENVars::NAME_PLANT_01 != "") {
            FLC::FlowerData data_01(ENVars::NAME_PLANT_01, moisture_01);
            data_01.Post();
        }

        if (ENVars::NAME_PLANT_02 != "") {
            FLC::FlowerData data_02(ENVars::NAME_PLANT_02, moisture_02);
            data_02.Post();
        }

        if (isnan(event.temperature)) Serial.println(F("Error reading temperature!"));
        else {

            if (ENVars::NAME_TEMP != "") {
                FLC::TempData temp_data(ENVars::NAME_TEMP, temperature);
                temp_data.Post();
            }   
        }
    }   

    delay(ENVars::REFRESH_RATE);
}