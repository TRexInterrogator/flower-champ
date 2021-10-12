#include "tempData.h"



using namespace FLC;
using namespace ENV;


TempData::TempData() { }


TempData::TempData(String sensor_name, float sensor_data) {
    
    this->_sensor_name = sensor_name;
    this->_temp_deg = roundf(sensor_data * ENVars::TEMP_OFFSET);

    Serial.println("Sensor: " + this->_sensor_name + " - " + this->_temp_deg + " Celcius");
}


String TempData::ToJson() {
    String json = R"===(
        {
            "sensor_id": "@sensor_id",
            "sensor_value": @sensor_value,
            "raw_value": @raw_value
        }
    )===";


    json.replace("@sensor_id", this->_sensor_name);
    json.replace("@sensor_value", String(this->_temp_deg));
    json.replace("@raw_value", String(this->_temp_deg));

    return json;
}


void TempData::Post() {
    HTTPClient http;
    String url = ENVars::WEBHOOK + "/?accessoryId=" + this->_sensor_name + "&value=" + this->_temp_deg;

    http.begin(url);
    http.GET();
    http.end();
}