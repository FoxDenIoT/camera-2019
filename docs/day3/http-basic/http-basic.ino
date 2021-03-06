#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "test";
const char* password = "12345678";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleNotFound() {
  server.send(200, "text/plain", "404 Error");
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  IPAddress apIP = IPAddress(1, 1, 1, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  char buff[128];
  sprintf(buff, "%s", ssid);

  if (!WiFi.softAP(buff, password, 1, 0)) {
      Serial.println("AP Begin Failed.");
      while (1);
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
