#include "enesheaders.h"
#include <math.h>
#include <Enes100.h>

// make a way to course correct the angle while driving

float distance = 0.;
float duration = 0.;



struct RGB {
  float r;
  float g;
  float b;

};

struct Point {
  float x;
  float y;
  float theta;
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

void activate_press() {
  pressServo.write(255);
  delay(5000);
  pressServo.write(0);
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
        analogWrite(BOTH_MOTORS_PWM,100);
    }
    //  while((newAngle - 0.01) > Enes100.getTheta() || Enes100.getTheta() > (newAngle + 0.01)){
    //     Tank.setRightMotorPWM(10 * pref);
    //     Tank.setLeftMotorPWM(-10 * pref);
    //     angle = Enes100.getTheta();


    // }
    analogWrite(BOTH_MOTORS_PWM,0);
    Enes100.print("[Group 5]: ");
    Enes100.println(Enes100.getTheta());
}

bool is_obstacle() {
  return read_distance() < 300.;

}


/*

This function will stop moving automatically upon detecting an obstacle.

Do not use it for navigation that requires detecting obstacles

*/

// Angle seems to be correct only when the OTV is to  the left of the desired point. Strange.
// It breaks right after you pass by the point
// /!\ When past the point, the angle needs to become pi-theta
void go_to_coords(float x, float y, int speed) {
  Enes100.print("[Group 5] go_to_coords: ");
  Enes100.print(x);
  Enes100.print(" ");
  Enes100.println(y);
  Enes100.print("theta: ");
  // bug: navigating to a point with the same X coord will cause division by 0
  float theta;
  
  if ((y != Enes100.getY()) && (x != Enes100.getX())) {
    theta = atan((y-Enes100.getY())/(x-Enes100.getX()));
    if (Enes100.getX() > x) {
      theta -= PI;
    }
  }
  else if (x == Enes100.getX()) {
    theta = ((y-Enes100.getY() > 0) - (y-Enes100.getY() < 0)) * HALF_PI; // pi/2 or -pi/2 depending on sign
  }
  else if (y == Enes100.getY()) {
    theta = (x-Enes100.getX() > 0) ? 0 : -PI;
  }
  
  Enes100.println(theta);
  turn(theta);
  
  Enes100.println("Driving...");
  // when ultrasonic is disconnected, this will never run. commented out for now.
  while ( ((Math.abs(Enes100.getX() - x > 0.3)) || (Math.abs(Enes100.getY() - y > 0.3))) ) { //&& !is_obstacle()) {
    Enes100.print(" x ");
    Enes100.print(Enes100.getX());
    Enes100.print(" y ");
    Enes100.print(Enes100.getY());
    // if (Enes100.getTheta() != theta) {
    //   stop_moving();
    //   turn(theta);
    // } 
    // else {
    drive_forwards(speed);
    // }
    delay(10);
  }
  stop_moving();
}

void navigate_obstacles(float goal_x, float goal_y) {
  go_to_coords(0.1, 1, 100);
  float x, y;
  float theta = Enes100.getTheta();
  while ((x=Enes100.getX()) != goal_x || (y=Enes100.getY()) != goal_y) {
    // might get stuck
    // Liam's idea: obstacle counter??? there can only be 3

    turn(0);
    // turn up
    if (is_obstacle()) {
      turn(HALF_PI);
    // turn down (we have reached the top)
    }
    if (is_obstacle()) {
      turn(-HALF_PI);
    }

    // if neither condition is true, we will drive in the +x direction
    // May need to modify for shorter checking intervals
    drive_forwards(100);
    delay(500);
    stop_moving();
  }

}


bool is_orzo() {
    struct RGB rgb;
    rgb = read_rgb();
    return ((rgb.r/rgb.g) < 1.21 );
}


// is 0 the correct value?
void release_seed() {
  trapdoorServo.write(0);
}

/*
Assumes the OTV is already facing directly towards the plot and is in the correct position.
Will probably need fine-tuning

TODO: 
- hard code the points by manually checking them
*/
void go_to_plot(int plot, bool top) {
  plot += 4*top;
  struct Point plots[] {
    // bottom points
    {0., 0., 0.},
    {0., 0., 0.},
    {0., 0., 0.},
    {0., 0., 0.},
    // top points
    {0., 0., 0.},
    {0., 0., 0.},
    {0., 0., 0.},
    {0., 0., 0.}  
  };
  go_to_coords(plots[plot].x, plots[plot].y,100);
}

void perform_mission(int iters) {
  bool orzo_found;
  bool top;
  int plot = 0;
  int counter;
  // Navigate to mission site
  top = Enes100.getY() > 1.;
  if (top) {
    go_to_coords(0.55,0.55,100);
    turn(-HALF_PI);
  }
  else {
    go_to_coords(0.55,1.45,100);
    turn(HALF_PI);
  }

  while (!orzo_found) {
    go_to_plot((++plot) % 4, top);
    counter = 0;
    for (int i = 0; i < iters; i++) {
      counter += is_orzo();
    }
    orzo_found = (counter > iters / 2); 
  }
  //release_seed();
  go_to_plot((++plot) % 4, top);
  //collect_rocks();
}
