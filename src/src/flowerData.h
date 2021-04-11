#include <Arduino.h>
#include <HTTPClient.h>
#include "env.h"


#ifndef FLOWERDATA
#define FLOWERDATA

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