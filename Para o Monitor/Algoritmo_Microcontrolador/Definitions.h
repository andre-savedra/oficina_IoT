#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define TEST 0

//PINS:
#define ESP_RX 5 //GPIO5
#define ESP_TX 0 //GPIO0
byte pins[] = {12,13,14,15};
byte relays[] = {0,0,0,0};


/********************WEB SERVICE:************************/
#define STANDARD_SSID "Oficina_IB"
#define STANDARD_PSWD "senaimange"



AsyncWebServer server(80);

AsyncWebServerRequest *mySavedRequest;

#endif
