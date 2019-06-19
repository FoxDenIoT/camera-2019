#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#define SSD1306_ADDRESS 0x3c

#define I2C_SDA 21
#define I2C_SCL 22

SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
OLEDDisplayUi ui(&oled);


#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "test1234";
const char* password = "";

WebServer server(80);

void handleRoot(int a) {
  if(a == 1){
    // set screen to say "OPEN"
    oled.clear();
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    delay(50);
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "OPEN");
    oled.display();
  }
  else{
    //set screen to say "CLOSED"
    oled.clear();
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    delay(50);
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "CLOSED");
    oled.display();
  }
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
}

void handleNotFound() {
  server.send(404, "text/plain", "404 Error");
}

void setup(void) {
  oled.init();
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  IPAddress apIP = IPAddress(2, 2, 2, 2);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  char buff[128];
  sprintf(buff, "%s", ssid);

  if (!WiFi.softAP(buff, password, 1, 0)) {
      Serial.println("AP Begin Failed.");
      while (1);
  }

    
    server.on("/on", []() {
      handleRoot(1);
    });

    server.on("/off", []() {
      handleRoot(0);
    });

 
    server.on("/", []() {
      handleRoot(1);
    });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
