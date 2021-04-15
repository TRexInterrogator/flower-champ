#include <Arduino.h>
#include <HTTPClient.h>
#include "env.h"
#include "math.h"


#ifndef FLOWERDATA
#define FLOWERDATA
#define MAX_DRY 4095
#define MAX_WET 2330

namespace FLC {

    class FlowerData {
        private:
            String _sensor_name;
            String _sensor_value;

        public:
            FlowerData();
            FlowerData(String sensor_name, int sensor_data);
            String ToJson();
            void Post();
    };
}

#endif