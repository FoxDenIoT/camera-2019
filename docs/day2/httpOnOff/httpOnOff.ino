#include <Arduino.h>
String ip;

char * HOSTNAME = "test";
char * WifiPASS = "";

#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);


void setup() {
    Serial.begin(115200);

   uint8_t mac[6];
    char buff[128];
    WiFi.mode(WIFI_AP);
    IPAddress apIP = IPAddress(2, 2, 2, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    sprintf(buff, "%s", HOSTNAME);
    Serial.printf("Device AP Name:%s\n", buff);
    if (!WiFi.softAP(buff, WifiPASS, 1, 0)) {
        Serial.println("AP Begin Failed.");
        while (1);
    }

    
    // handle index -- HTTP Server
    
    server.on("/on", []() {
      oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "OPEN");
      oled.display();
      server.send(200, "");
    });

    server.on("/off", []() {
      oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "CLOSE");
      oled.display();
      server.send(200, "");
    });
 
    server.begin();

    oled.init();
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    delay(50);
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "test");
    oled.display();
    
}

void loop() {
    server.handleClient();
}
