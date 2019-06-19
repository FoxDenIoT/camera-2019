#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#define SSD1306_ADDRESS 0x3c

#define I2C_SDA 21
#define I2C_SCL 22

SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
OLEDDisplayUi ui(&oled);


String inData;

void setup() {
  // initialize serial:
  Serial.begin(115200);

    oled.init();
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    delay(50);
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Type to Serial");
    oled.display();
}

void loop() {
    while (Serial.available() > 0)
    {
        char received = Serial.read();
        inData += received; 

        // Process message when new line character is recieved
        if (received == '\n')
        {
            Serial.print("Message received: ");
            Serial.print(inData);
            oled.clear();
            oled.setTextAlignment(TEXT_ALIGN_CENTER);
            oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, inData);
            oled.display();

            inData = ""; // Clear recieved buffer
        }
    }
}
