# Flower Champ

AZDelivery ESP32 moisture sensor for open API integration.

# WiFi credentials
You need to create `env.h` in **"main"** folder. Here you can add your WiFi credentials.
```env.h
#include <Arduino.h>

#ifndef ENV_H
#define ENV_H

namespace ENV {
    const String SSID = "mywifi";
    const String WiFiPwd = "password";
}

#endif
```


# Sample Webserver
Use **webserver** branch for testing and measuring your plants.
Connect to WiFi **Flower Champ** and use **flowerpower** as password.
