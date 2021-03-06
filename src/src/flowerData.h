#include <Arduino.h>
#include <HTTPClient.h>
#include "env.h"


#ifndef FLOWERDATA
#define FLOWERDATA
#define MAX_DRY 3700
#define MAX_WET 1700
#define MAX_WET_V2 1300

namespace FLC {

    class FlowerData {
        private:
            String _sensor_name;
            String _sensor_value;
            int _raw_value;

        public:
            FlowerData();
            FlowerData(String sensor_name, int sensor_data);
            String ToJson();
            void Post();
    };
}

#endif