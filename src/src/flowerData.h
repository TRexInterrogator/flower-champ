#include <Arduino.h>
#include <HTTPClient.h>
#include "env.h"


#ifndef FLOWERDATA
#define FLOWERDATA
#define MAX_DRY 2850
#define MAX_WET_V2 940

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