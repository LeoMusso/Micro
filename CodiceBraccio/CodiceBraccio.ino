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
