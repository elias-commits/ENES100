#include "enesheaders.h"

float distance = 0.;
float duration = 0.;

struct RGB {
  float r;
  float g;
  float b;

};

float read_distance() {
    digitalWrite(ULTRASONIC_TRIGGER,LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIGGER,HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER,LOW);

    duration = pulseIn(ULTRASONIC_ECHO,HIGH);
    distance = (duration*0.343)/2;

    return distance;//(pulseIn(ULTRASONIC_ECHO,HIGH)*0.343)/2;
}

// add a function to calculate speed from PWM?
// currently takes raw PWM value

void drive_left(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    digitalWrite(R_MOTOR_DIRECTION,0);
    digitalWrite(L_MOTOR_DIRECTION,1);

}

float read_red() {
  digitalWrite(COLOR_S2,LOW);
  digitalWrite(COLOR_S3,LOW);

  return pulseIn(COLOR_INPUT, digitalRead(COLOR_INPUT) == HIGH ? LOW : HIGH);
}

float read_green() {
  digitalWrite(COLOR_S2,HIGH);
  digitalWrite(COLOR_S3,HIGH);

  return pulseIn(COLOR_INPUT, digitalRead(COLOR_INPUT) == HIGH ? LOW : HIGH);
}


float read_blue() {
  digitalWrite(COLOR_S2,LOW);
  digitalWrite(COLOR_S3,HIGH);
  
  return pulseIn(COLOR_INPUT, digitalRead(COLOR_INPUT) == HIGH ? LOW : HIGH);
}

struct RGB read_rgb() {
  struct RGB ret;
  
  ret.r = read_red();
  delay(2);
  ret.g = read_blue();
  delay(2);
  ret.b = read_green();
  delay(2);

  return ret;
}



void drive_forward(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    digitalWrite(R_MOTOR_DIRECTION,1);
    digitalWrite(L_MOTOR_DIRECTION,1);
}

void drive_right(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    digitalWrite(R_MOTOR_DIRECTION,1);
    digitalWrite(L_MOTOR_DIRECTION,0);
}
