#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>



#define SENSOR_01 33
#define MAX_DRY 4095
#define MAX_WET 2330
#define PALME_DRY 4090


const String indexHTML = R"===(
    <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta http-equiv="X-UA-Compatible" content="IE=edge">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Flower-Champ</title>
        </head>
        <body>
            <h1>Flower Champ</h1>

            <br />
            <br />

            <p>Moisture level: <b>@moisture</b></p>
        </body>
    </html>
)===";


WebServer server(80);
IPAddress apIP(192, 168, 0, 1);


int moisture_01 = 0;
int hm_range = (MAX_DRY - MAX_WET) / 3;
int upper_range = MAX_DRY - hm_range;
int lower_range = MAX_WET + hm_range;



void OnIndexPage() {
    String website = indexHTML;
    website.replace("@moisture", String(moisture_01));
    server.send(200, "text/html", website);
}


void On404() {
    server.send(404, "text/plain", "Not found");
}


void setup() {
    Serial.begin(9600);
    Serial.println("Starting webserver");
    pinMode(SENSOR_01, INPUT);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("Flower Champ", "flowerpower");
    server.on("/", OnIndexPage);
    server.onNotFound(On404);

    delay(1000);

    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    server.begin();
    Serial.println("Webserver running");
}


void loop() {   
    server.handleClient();
    moisture_01 = analogRead(SENSOR_01);

    String output_01 = "Moisture level 01: ";
    output_01.concat(String(moisture_01));
    Serial.println(output_01);

    delay(2000);
}