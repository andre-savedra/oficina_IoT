#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Definitions.h"
#include "LandingPage.h"
/*
#if (TEST)
#include "LandingPage.ino"
#endif
*/

void setup()
{  
  //start marlin communication
  Serial.begin(115200);

  /************ WIFI *************/
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_AP);
    delay(1000);

    IPAddress staticIP(192, 168, 10, 17);
    IPAddress gateway(192, 168, 10, 1);
    IPAddress subnet(255, 255, 255, 0);

    Serial.println("CONFIG IP...");
    Serial.println(WiFi.softAPConfig(staticIP, gateway, subnet));

    Serial.println("SSID E SENHA...");
    Serial.println(WiFi.softAP(STANDARD_SSID, STANDARD_PSWD));
    
    Serial.println("IP...");
    Serial.println(WiFi.softAPIP());
    
  /************** WEB SERVICE ***************/
  server.onNotFound(notFound);
 
    // Root:
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      
      request->send_P(200, "text/html", index_html); 
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
