#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600

void setup(){
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(100);
}

int n = 0;

void loop(){
  for(int a = SERVOMIN; a <= SERVOMAX; a++){
    pwm.setPWM(n, 0, a);
    delay(1);
  }

  delay(100);

  for(int a = SERVOMAX; a >= SERVOMIN; a--){
    pwm.setPWM(n, 0, a);
    delay(1);
  }

  n++;
  if(n >= 3) n = 0;
}
