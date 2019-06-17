#include <OneButton.h>
#define BUTTON_1 34

#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#define SSD1306_ADDRESS 0x3c

#define I2C_SDA 21
#define I2C_SCL 22

SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
OLEDDisplayUi ui(&oled);
char cstr[16];


OneButton button1(BUTTON_1, true);
int count = 0;
void button1Func()
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
    button1Func();
    
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();
    button1.attachClick(button1Func);
}

void loop(){

        button1.tick();


}
