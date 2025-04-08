#include <Enes100.h>
#include <Servo.h>
#include "enesfunctions.h"


void setup() {
  Enes100.begin("Group 5", SEED, 9, 1120, WIFI_TX, WIFI_RX);
  Serial.begin(9600);
 for (int i = 0; i < (sizeof(INPUT_PINS) / sizeof(int)); i++) {
        pinMode(INPUT_PINS[i],INPUT);
    }
  for (int i = 0; i < (sizeof(OUTPUT_PINS) / sizeof(int)); i++) {
        pinMode(OUTPUT_PINS[i],OUTPUT);
    }
pinMode(ULTRASONIC_TRIGGER, OUTPUT);  
pinMode(ULTRASONIC_ECHO, INPUT);
Serial.println("Test1");


}


void loop() {
// Serial.println("Red: ");
//  Serial.println(read_red());
//  Serial.println("Green: ");
//  Serial.println(read_green());
//  Serial.println("Blue: ");
//  Serial.println(read_blue());
//  delay(1000);


// myservo.attach(11);
//   myservo.write(0);
//   delay(500);
//   myservo.write(45);
//   delay(500);
//   myservo.write(90);
//   delay(500);
//   myservo.write(135);
//   delay(500);
//   myservo.write(180);
//   delay(500);
//   myservo.write(135);
//   delay(500);
//   myservo.write(90);
//   delay(500);
//   myservo.write(45);


// myservo2.attach(5);
//  myservo2.write(0);
//   delay(500);
//   myservo2.write(45);
//   delay(500);
//   myservo2.write(90);
//   delay(500);
//   myservo2.write(135);
//   delay(500);
//   myservo2.write(180);
//   delay(500);
//   myservo2.write(135);
//   delay(500);
//   myservo2.write(90);
//   delay(500);
//   myservo2.write(45);


//  digitalWrite(ULTRASONIC_TRIGGER, LOW);
//   delayMicroseconds(2);
//   digitalWrite(ULTRASONIC_TRIGGER, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(ULTRASONIC_TRIGGER, LOW);


//   duration = pulseIn(ULTRASONIC_ECHO, HIGH);
//   distance = (duration*.0343)/2;
//   Serial.print("Distance: ");
//   Serial.println(distance);
//   delay(100);


// Serial.println("Forwards");
//     drive_forwards(255);
//     delay(1000);
//     Serial.println("Backwards");
//     drive_backwards(255);
//     delay(1000);
 
// Enes100.println("\nX: ");
// Enes100.println(Enes100.getX());
// Enes100.println("\nY: ");
// Enes100.println(Enes100.getY());
// Enes100.println("\nTheta: ");
// Enes100.println(Enes100.getTheta());
Enes100.mission(LOCATION, 'A');
Serial.println("Test");
Serial.println("\nX: ");
Serial.println(Enes100.getX());
Serial.println("\nY: ");
Serial.println(Enes100.getY());
Serial.println("\nTheta: ");
Serial.println(Enes100.getTheta());


delay(5000);
}
