#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "test1234";
const char* password = "";

WebServer server(80);
static const uint8_t LED_PIN = 21;
static const uint8_t LED_PIN1 = 22;


void handleRoot(int a) {
  if(a == 1){
    // turn on led
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN1, LOW);
  }
  else{
    //turn off led
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN1, HIGH);
  }
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
}

void handleNotFound() {
  server.send(404, "text/plain", "404 Error");
}

void setup(void) {
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

    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_PIN1, OUTPUT);
    
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
