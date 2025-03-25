#include "enesmacros.h"

float read_distance() {
    float distance = 0.;
    float duration = 0.;
    digitalWrite(ULTRASONIC_TRIGGER,LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIGGER,HIGH);
    delayMicroseconds(10);
  
    duration = pulseIn(ULTRASONIC_ECHO,HIGH);
    distance = (duration*0.343)/2;
    return distance;
}

// add a function to calculate speed from PWM?
// currently takes raw PWM value

void turn_left(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    digitalWrite(R_MOTOR_DIRECTION,0);
    digitalWrite(L_MOTOR_DIRECTION,1);

}

void drive_forward(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    digitalWrite(R_MOTOR_DIRECTION,0);
    digitalWrite(L_MOTOR_DIRECTION,1);
}

void turn_right(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    digitalWrite(R_MOTOR_DIRECTION,1);
    digitalWrite(L_MOTOR_DIRECTION,0);
}
