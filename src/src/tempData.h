#include <Arduino.h>
#include <HTTPClient.h>
#include "env.h"
#include "math.h"


#ifndef TEMPDATA

namespace FLC {

    class TempData {
        private:
            String _sensor_name;
            float _temp_deg;

        public:
            TempData();
            TempData(String sensor_name, float sensor_data);
            String ToJson();
            void Post();
    };
}

#endif