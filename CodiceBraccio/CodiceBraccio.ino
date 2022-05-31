/*#include <Servo.h>
Servo Base;
Servo BraccioV;
Servo BraccioG;
Servo Pinza;


//PARI APRONO
//DISPARI CHIUDONO

int pulsBaseA = 2;
int pulsBaseC = 3; 
int pulsBraccioA = 4;
int pulsBraccioC = 5;
int pulsPinzaA = 6;
int pulsPinzaC = 7;
int pos = 1;
int posP = 1;
void setup() {
  pinMode(pulsBaseA, INPUT);
  pinMode(pulsBaseC, INPUT);
  pinMode(pulsBraccioA, INPUT);
  pinMode(pulsBraccioC, INPUT);
  Base.attach(8);
  BraccioV.attach(9);
  BraccioG.attach(10);
  Pinza.attach(11);
  Base.write(pos);
  /*BraccioV.write(pos);
  BraccioG.write(pos);
  Pinza.write(pos); 
  Serial.begin(9600);
}

int incrementaBase(int puls){
    if(digitalRead(puls) == HIGH && (pos < 191  && pos > 0)){
    pos += 10;
  }
  return pos;
}
int decrementaBase(int puls){
  if(digitalRead(puls) == HIGH && (pos > 1 && pos < 192)){
    pos -= 10;
  }
  return pos;
}

int incrementaPinza(int puls){
  if(digitalRead(puls) == HIGH && (posP < 191  && posP > 0)){
    pos += 10;
  }
  return posP;
}

int decrementaPinza(int puls){
  if(digitalRead(puls) == HIGH && (posP > 1 && posP < 192)){
    pos -= 10;
  }
  return posP;
}

void loop() {
  pos = incrementaBase(pulsBaseA);
  pos = decrementaBase(pulsBaseC);
  posP = incrementaPinza(pulsPinzaA);
  posP = decrementaPinza(pulsPinzaC);
  Base.write(pos);
  Pinza.write(posP);
  Serial.print("Pos: ");
  Serial.println(pos);
  Serial.print("PosP: ");
  Serial.println(posP);
  delay(100);
}*/

#include <Adafruit_PWMServoDriver.h>

#define JOYSTICK1_X_PIN A1
#define JOYSTICK1_Y_PIN A0
#define JOYSTICK2_X_PIN A3
#define JOYSTICK2_Y_PIN A2
#define THRESHOLD 30
#define SERVO_MIN 150
#define SERVO_MAX 600 

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

float positions[4] = {60, 140, 85, 100}; // RIGHT, TOP, BOTTOM, LEFT

void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop() {
  moveServo(0, analogRead(JOYSTICK2_X_PIN), true);
  moveServo(1, analogRead(JOYSTICK2_Y_PIN), false);
  moveServo(2, analogRead(JOYSTICK1_Y_PIN), false);
  moveServo(3, analogRead(JOYSTICK1_X_PIN), true);
  delay(50);
}

void moveServo(int index, int value, bool reverse) {
  if (abs(value - 512) > THRESHOLD) {
    float delta = (float) (value - 512) / 100;
    if (reverse) {
      positions[index] -= delta;
    } else {
      positions[index] += delta;
    }
    positions[index] = constrain(positions[index], 0, 179);
  }
  
  int pulse = map(positions[index], 0, 179, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(index, 0, pulse);
}
