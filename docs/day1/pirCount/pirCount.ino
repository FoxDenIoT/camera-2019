#define PIR_PIN 33

#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#define SSD1306_ADDRESS 0x3c

#define I2C_SDA 21
#define I2C_SCL 22

SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
OLEDDisplayUi ui(&oled);
char cstr[16];
int PIRState = 0;


int count = 0;
void countFunc()
{
    oled.clear();
    sprintf(cstr, "%d", count);
    oled.drawString(oled.getWidth() / 2, 20, cstr);
    oled.display();
    
    count++;
}

void setup()
{
    oled.init();
    oled.setFont(ArialMT_Plain_24);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    delay(50);
    countFunc();
    
    pinMode(PIR_PIN, INPUT);

}

void loop(){ 
  if (digitalRead(PIR_PIN) == HIGH) 
  {
    countFunc();
  } 

  delay(1000);
}
