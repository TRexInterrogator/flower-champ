# Flower Champ

AZDelivery ESP32 moisture sensor for open API integration.

# WiFi credentials
You need to create `env.cpp` in **"main"** folder. Here you can add your WiFi credentials.
Your compiler might give you warnings about strig constat conversion. 

```env.cpp
#include "env.h"

String ENV::ENVars::API = "http://192.168.178.34/yepp";
char* ENV::ENVars::SSID = "YOUR SSID";
char* ENV::ENVars::WiFiPwd = "YOUR WiFi PASSWORD";
```


# Sample Webserver
Use **webserver** branch for testing and measuring your plants.
Connect to WiFi **Flower Champ** and use **flowerpower** as password.
