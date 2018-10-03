int value[4];

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()){
    int count = 0;
    for (int i = 0; i < 4; i++) value[i] = 0;
    while (Serial.available()){
      char temp = Serial.read();
      if (temp - '0' < 10 && temp - '0' >= 0) value[count] = value[count]*10 + temp - '0';
      else if (temp == '-') count++;
      else if (temp == '|') break;
      delay(1);//the data won't be complete without a delay
    }
  
    //check values
    for (int i = 0 ; i < 4; i++){
      Serial.print(value[i]);
      Serial.print(' ');
    }
    Serial.println();
  }
}
