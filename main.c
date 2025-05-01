#include <Enes100.h>
#include "enesfunctions.h"
#include <Servo.h>


float dist;

void setup() {
    Serial.begin(9600);
    pressServo.attach(PRESS_SERVO_PWM);
    trapdoorServo.attach(TRAPDOOR_SERVO_PWM);
    for (int i = 0; i < (sizeof(INPUT_PINS) / sizeof(int)); i++) {
        pinMode(INPUT_PINS[i],INPUT);
    }
    for (int i = 0; i < (sizeof(OUTPUT_PINS) / sizeof(int)); i++) {
        pinMode(OUTPUT_PINS[i],OUTPUT);
    }
}


void loop() {
  Serial.println("Test");
  digitalWrite(R_MOTOR_DIRECTION1,HIGH);
  digitalWrite(R_MOTOR_DIRECTION2,0);
  digitalWrite(L_MOTOR_DIRECTION1,1);
  digitalWrite(L_MOTOR_DIRECTION2,0);
  analogWrite(BOTH_MOTORS_PWM,150);
  delay(1000);

    // Serial.println("drive_forwards(100)");
    // drive_forwards(100);
    // delay(10000);
    // Serial.println("drive_forwards(50)");
    // delay(10000);
    // Serial.println("drive_backwards(100");
    // drive_backwards(100);
    // delay(10000);
    // Serial.println("drive_backwards(50)");
    // drive_backwards(50);
    // Serial.println("drive_left(100)");
    // drive_left(100);
    // delay(10000);
    // Serial.println("drive_right(100)");
    // drive_left(100);
    // delay(10000);
    // Serial.println("read_distance()");
    // dist = read_distance();
    // Serial.println(dist);
    // delay(300);
    // Serial.println("read_rgb()");
    // struct RGB ret;
    // ret = read_rgb();
    // Serial.println(ret.r);
    // Serial.println(ret.g);
    // Serial.println(ret.b);

    //Serial.println(ret.r/ret.g);
    //Serial.println(ret.r/ret.b);
    // if (is_orzo()) {
    //   Serial.println("Orzo detected!");
    // }
  
    // else {
    //   Serial.println("Rocks detected!");
    // }
    // delay(1000);
    // Serial.println("Servos go in opposite directions");
    // Serial.println(is_obstacle());

  //   int pos;
  //   for (pos = 0; pos <= 180; pos += 10) {
  //       pressServo.write(pos);
  //       trapdoorServo.write(180 - pos);
  //       delay(100);
  // }
}
