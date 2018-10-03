/* Serial Loop */

#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
char myChar ;

void setup() {
  Serial.begin(115200);   
  Serial.println("AT");

  mySerial.begin(115200);
  mySerial.println("AT");
}

void loop() {
  while (mySerial.available()) {
    myChar = mySerial.read();
    Serial.print(myChar);
  }

  while (Serial.available()) {
    myChar = Serial.read();
    Serial.print(myChar); //echo
    mySerial.print(myChar);
  }
}
