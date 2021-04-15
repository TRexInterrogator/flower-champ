#include "flowerData.h"

using namespace FLC;
using namespace ENV;


FlowerData::FlowerData() { }


FlowerData::FlowerData(String sensor_name, int sensor_data) {

    this->_sensor_name = sensor_name;

    if (sensor_data >= 2330) this->_sensor_value = String(((int)ceil((MAX_DRY - sensor_data) * 0.056f)));
    else this->_sensor_value = "0";
}


String FlowerData::ToJson() {
    String json = R"===(
        {
            "id": null,
            "sensor_id": "@sensor_id",
            "sensor_value": @sensor_value,
            "date_time": null,
            "date_date": null
        }
    )===";

    json.replace("@sensor_id", this->_sensor_name);
    json.replace("@sensor_value", String(this->_sensor_value));

    return json;
}


void FlowerData::Post() {
    HTTPClient http;
    String url = ENVars::API + String("/flowerData/new");

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.POST(this->ToJson());
    http.end();
}