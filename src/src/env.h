#ifndef ENV_H
#define ENV_H

#include <Arduino.h>


namespace ENV {
    class ENVars {
        public:
            static char* SSID;
            static char* WiFiPwd;
            static String WEBHOOK;
            static float TEMP_OFFSET;
            static int REFRESH_RATE;
            static String NAME_TEMP;
            static String NAME_PLANT_01;
            static String NAME_PLANT_02;
    };
}

#endif