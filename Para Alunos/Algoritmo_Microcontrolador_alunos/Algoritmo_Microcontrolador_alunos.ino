#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Definitions.h"
#include "LandingPage.h"


void setup()
{  
  //start marlin communication
  Serial.begin(115200);

  /************ WIFI *************/
  //CONFIGURE O MODO DA REDE E AS CONFIGURAÇÕES DO IP AQUI
    

    
  /************** WEB SERVICE ***************/
  server.onNotFound(notFound);
 
    // Root:
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      
      //ADICIONE O NOME DA VARIÁVEL QUE CONTÉM O HTML AQUI
      request->send_P(200, "text/html", ); 
    });
  

  // Buttons Request:
  server.on("/buttons", HTTP_GET, [](AsyncWebServerRequest *request) {
    String message = "";    
    String req;
    
    for(int i=0;i<sizeof(relays);i++) {
        int idx = i + 1;
        message = "relay" + String(idx);

        if ((request->hasParam(message)) && (request->hasParam("status")) )
        {
          relays[i] = (request->getParam("status")->value().equals("true"))? 1 : 0;          
        } 
    }   

  });

  // Start server
  server.begin();

  for(int i=0; i<sizeof(pins); i++)
  {
    pinMode(pins[i], OUTPUT);
  }
  
}

void loop()
{
  //*****************HOME TASK*********************
  for(int i=0; i<sizeof(relays); i++){
    digitalWrite(pins[i],!relays[i]);
  }
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}
