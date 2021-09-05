#ifndef ENV_H
#define ENV_H

#include <Arduino.h>


namespace ENV {
    class ENVars {
        public:
            static char* SSID;
            static char* WiFiPwd;
            static String WEBHOOK;
    };
}

#endif