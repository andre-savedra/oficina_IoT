#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define TEST 0

//PINS:
#define ESP_RX 5 //GPIO5
#define ESP_TX 0 //GPIO0

//DEFINA OS PINOS E VARIÁVEIS RELÉS AQUI:


/********************WEB SERVICE:************************/
//DEFINA O NOME E SENHA DA REDE AQUI:



AsyncWebServer server(80);

AsyncWebServerRequest *mySavedRequest;

#endif
