#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#define SSD1306_ADDRESS 0x3c

#define I2C_SDA 21
#define I2C_SCL 22

SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
OLEDDisplayUi ui(&oled);



//FrameCallback frames[] = {drawFrame1, drawFrame2};
#define FRAMES_SIZE (sizeof(frames) / sizeof(frames[0]))



void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();


    oled.init();
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    delay(50);
}

void loop(){
    oled.clear();
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "HELLO");
    oled.display();
    delay(1000);
    
    oled.clear();
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "WORLD");
    oled.display();
    delay(1000);

}
