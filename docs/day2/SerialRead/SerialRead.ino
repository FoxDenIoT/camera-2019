String inData;

void setup() {
  // initialize serial:
  Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

  // reserve 200 bytes for the inputString:
}

void loop() {
    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            Serial.print("Message Received: ");
            Serial.print(inData);

            int x = inData.toInt();
            if(x == 1){
               digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            }
            else if (x == 0){
               digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
            }

            inData = ""; // Clear recieved buffer
        }
    }
}
