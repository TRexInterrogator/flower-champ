#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "env.h"
#include "flowerData.h"


using namespace ENV;


#define SENSOR_01 33
#define SENSOR_02 32


#define READ_INTERVAL 10000
#define POST_INTERVAL 360
#define SENSOR_01_NAME "Flower-Champ-Ficus"
#define SENSOR_02_NAME "Flower-Champ-Palme"


int moisture_01 = 0;
int moisture_02 = 0;
unsigned int updates = 0;
AsyncWebServer server(80);


// REST endpoint for requesting current Sensor data
void OnDataRequested(AsyncWebServerRequest *request) {

    FLC::FlowerData data_01(SENSOR_01_NAME, moisture_01);
    FLC::FlowerData data_02(SENSOR_02_NAME, moisture_02);
    String response = "[" + data_01.ToJson() + "," + data_02.ToJson() + "]";
    request->send(200, "application/json", response);
}

void OnNotFound(AsyncWebServerRequest *request) {
    request-> send(404, "appliction/json", "Not found");
}


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

    // Basic json web api
    server.on("/", HTTP_GET, OnDataRequested);
    server.onNotFound(OnNotFound);
    server.begin();
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
        // Send data every 60 mins.
        updates = 0;

        if (WiFi.status() == WL_CONNECTED) {
            FLC::FlowerData data_01(SENSOR_01_NAME, moisture_01);
            FLC::FlowerData data_02(SENSOR_02_NAME, moisture_02);

            data_01.Post();
            data_02.Post();

            Serial.println("Sensor data POST complete");
        }
    }    
}