#include "enesheaders.h"
#include <math.h>
#include <Enes100.h>

float distance = 0.;
float duration = 0.;



struct RGB {
  float r;
  float g;
  float b;

};

// milimeters
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
  int passes = 50;
  for (int i = 0; i < passes; i++) {
    ret.r += read_red();
    delay(1);
    ret.g += read_green();
    delay(1);
    ret.b += read_blue();
    delay(1);
  }
  ret.r /= passes;
  ret.g /= passes;
  ret.b /= passes;
  return ret;
}


void right_forwards() {
  digitalWrite(R_MOTOR_DIRECTION1,1);
  digitalWrite(R_MOTOR_DIRECTION2,0);
}

void left_forwards() {
  digitalWrite(L_MOTOR_DIRECTION1,1);
  digitalWrite(L_MOTOR_DIRECTION2,0);
}

void right_backwards() {
  digitalWrite(R_MOTOR_DIRECTION1,0);
  digitalWrite(R_MOTOR_DIRECTION2,1);
}

void left_backwards() {
  digitalWrite(L_MOTOR_DIRECTION1,0);
  digitalWrite(L_MOTOR_DIRECTION2,1);
}

void drive_forwards(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    right_forwards();
    left_forwards();
}

void stop_moving() {
  drive_forwards(0);
}

void drive_backwards(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    right_backwards();
    left_backwards();
}

void drive_left(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    left_forwards();
    right_backwards();

}

void drive_right(int speed) {
    analogWrite(BOTH_MOTORS_PWM,speed);
    right_forwards();
    left_backwards();
}

void turn(double newAngle){
    double angle = Enes100.getTheta();
    int pref;


    if((angle - newAngle > 0 && PI > angle - newAngle) || (angle - newAngle > -1*TWO_PI && -1*PI > angle - newAngle)){
      
      right_backwards();
      left_forwards();
    }
    else{
      right_forwards();
      left_backwards();
    }


    while((newAngle - 0.3) > Enes100.getTheta() || Enes100.getTheta() > (newAngle + 0.3)){
        analogWrite(BOTH_MOTORS_PWM,50);
    }
    //  while((newAngle - 0.01) > Enes100.getTheta() || Enes100.getTheta() > (newAngle + 0.01)){
    //     Tank.setRightMotorPWM(10 * pref);
    //     Tank.setLeftMotorPWM(-10 * pref);
    //     angle = Enes100.getTheta();


    // }
    analogWrite(BOTH_MOTORS_PWM,0);
    Enes100.println(Enes100.getTheta());
}

/*
This function will stop moving automatically upon detecting an obstacle.
*/
void go_to_coords(float x, float y, int speed) {
  float theta = atan((y-Enes100.getY())/(x-Enes100.getX()));
  turn(theta);
  drive_forward(speed);
  while ( ( (Enes100.getX() != x) || (Enes100.getY() != y) ) && !is_obstacle())) {
    delay(10);
  }
  stop_moving();
}


bool is_obstacle() {
  return read_distance() < 300.;

}

bool is_orzo() {
    struct RGB rgb;
    rgb = read_rgb();
    return ((rgb.r/rgb.g) < 1.21 );
}
