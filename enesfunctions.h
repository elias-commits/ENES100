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
