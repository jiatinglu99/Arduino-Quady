long lastConnection, nowConnection;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available())// && micros() < 10000000)
  {
    char character = Serial.read();
    Serial.print(character);
    if (character == '-'){
      nowConnection = micros();
      Serial.println(nowConnection - lastConnection);
      lastConnection = nowConnection;
    }
  }
}
