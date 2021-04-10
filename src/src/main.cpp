#include <Arduino.h>


#define SENSOR_01 12
#define SENSOR_02 14

#define MAX_DRY 4095
#define MAX_WET 2330

#define PALME_DRY 4090


int moisture_01 = 0;
int moisture_02 = 0;

int hm_range = (MAX_DRY - MAX_WET) / 3;
int upper_range = MAX_DRY - hm_range;
int lower_range = MAX_WET + hm_range;


void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_01, INPUT);
    pinMode(SENSOR_02, INPUT);
}


void loop() {   
    moisture_01 = analogRead(SENSOR_01);
    moisture_02 = analogRead(SENSOR_02);

    String output_01 = "Moisture level 01: ";
    output_01.concat(String(moisture_01));
    Serial.println(output_01);

    String output_02 = "Moisture level 01: ";
    output_02.concat(String(moisture_02));
    Serial.println(output_02);

    if (moisture_01 < PALME_DRY) {
        Serial.println("PALME 01 OK");
    }
    else {
        Serial.println("PALME 01 WASSER!");
    }

    if (moisture_02 < PALME_DRY) {
        Serial.println("PALME 02 OK");
    }
    else {
        Serial.println("PALME 02 WASSER!");
    }
    

    delay(2000);
}