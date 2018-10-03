#define fadePin 3
#define m1Pin 3
#define m2Pin 5
#define m3Pin 6
#define m4Pin 9

int value[5];
int c = 0;
int cc = 0;
bool firstTime = true;
long lastConnection, firstConnection;

class Motor{
public:
  int pin;
  double sinOut;
  Motor();
  void Init (int tpin){
    pin = tpin;
  }
  void writeSinout(double temp)
  {
    sinOut = temp;
    analogWrite(fadePin, sinOut);
  }
};

Motor::Motor (){}

class Central{
public:
  Motor m1, m2, m3, m4;
  int x1, x2, y1, y2;
  int baseValue;
  Central();
  void Init(int tm1, int tm2, int tm3, int tm4){
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    baseValue = 0;
    m1.Init(tm1);
    m2.Init(tm2);
    m3.Init(tm3);
    m4.Init(tm4);
  }
  void dataUpdate(int a, int b, int c, int d){
    x1 = a;
    y1 = b;
    x2 = c;
    y2 = d;
  }
  void process(){
    baseValue = map(x1, 0, 999, 0, 255);
  }
} central;

Central::Central (){}

void setup(){
  pinMode(fadePin, OUTPUT);
  Serial.begin(115200);
  //central.Init(m1Pin, m2Pin, m3Pin, m4Pin);
  //lastConnection = micros();
}

void loop(){
  bluetoothRead();
  fan();
  //central.dataUpdate(value[0], value[1], value[2], value[3]);
  //central.process();
}

void bluetoothRead(){
  //if (Serial.available())Serial.write(Serial.read());
  if (Serial.available()){
    char checkStart = Serial.read();
    if (checkStart == '-'){
      if (firstTime) {
        firstConnection = micros();
        firstTime = false;
      }
      if (micros() < firstConnection + 10000000){
          //Serial.print(" ");
          //Serial.print(micros());
          //Serial.print(" ");
          //Serial.print(lastConnection);
          //Serial.print(" ");
          //Serial.println(micros() - lastConnection);
      }
      lastConnection = micros();
      delay(5);
      int tvalue[5];//temporary value: making sure that it doesn't receive 0
      int subCount = 0;
      int count = 0;
      for (int i = 0; i < 5; i++) tvalue[i] = 0;
      while (Serial.available()){
        char temp = Serial.read();
        if (temp - '0' < 10 && temp - '0' >= 0) tvalue[count] = tvalue[count]*10 + temp - '0';
        if (temp == '|') break;
        subCount++;
        if (subCount >= 3) {
          count++;
          subCount = 0;
        }
        delay(5);//the data won't be complete without a delay
        cc++;
      }
    
      //check values
      //if (tvalue[0] != 0 || tvalue[1] != 0 || tvalue[2] != 0 || tvalue[3]! = 0) 
      for (int i = 0 ; i < 5; i++) value[i] = tvalue[i];
      //for (int i = 0 ; i < 5; i++){
        //Serial.print(tvalue[i]);
        //Serial.print(' ');
      //}
      ++c;
      //Serial.print(c);
      //Serial.print(' ');
      //Serial.print(cc);
      //Serial.println();
    }
  }
  else if (micros() > lastConnection + 1000000) for (int i = 0; i < 5; i++) {
    value[i] = 0;
  }
  
}
 
void fan(){//Temporary test 
 
  for(int i = 0; i<360; i++){
    //convert 0-360 angle to radian (needed for sin function)
    float rad = DEG_TO_RAD * i;
 
    //calculate sin of angle as number between 0 and 255
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255);

    sinOut = map(value[1], 0, 999, 0, 255);
    analogWrite(3, sinOut);
    analogWrite(5, sinOut);
    analogWrite(6, sinOut);
    analogWrite(9, sinOut);
 
    //Serial.println(sinOut);
    //delay(15);
  }
}
