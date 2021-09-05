#include "flowerData.h"

using namespace FLC;
using namespace ENV;


FlowerData::FlowerData() { }


FlowerData::FlowerData(String sensor_name, int sensor_data) {

    this->_sensor_name = sensor_name;
    this->_raw_value = sensor_data;

    if (sensor_data >= MAX_WET) {
        float calc_sensor = (100.0f / (float)(MAX_DRY - MAX_WET)) * (float)(MAX_DRY - sensor_data);
        this->_sensor_value = String(calc_sensor);
    }
    else this->_sensor_value = "0";

    Serial.println("Sensor: " + this->_sensor_name + " - " + this->_sensor_value);
}


String FlowerData::ToJson() {
    String json = R"===(
        {
            "sensor_id": "@sensor_id",
            "sensor_value": @sensor_value,
            "raw_value": @raw_value,
            "date_time": null,
            "date_date": null
        }
    )===";

    json.replace("@sensor_id", this->_sensor_name);
    json.replace("@sensor_value", String(this->_sensor_value));
    json.replace("@raw_value", String(this->_raw_value));

    return json;
}


void FlowerData::Post() {
    HTTPClient http;
    String url = ENVars::WEBHOOK + "/?accessoryId=" + this->_sensor_name + "&value=" + this->_sensor_value;

    http.begin(url);
    http.GET();
    http.end();
}