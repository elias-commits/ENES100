#define L_MOTOR_DIRECTION 13
#define BOTH_MOTORS_PWM 11
#define R_MOTOR_DIRECTION 9

#define PRESS_SERVO_PWM 10
#define TRAPDOOR_SERVO_PWM 5

// s2:LOW/s3LOW is RED, s2:HIGH/s3:HIGH is GREEN 
#define COLOR_S2 7 
#define COLOR_S3 2
#define COLOR_INPUT A0

#define ULTRASONIC_TRIGGER 3
#define ULTRASONIC_ECHO 8

int INPUT_PINS[] = {COLOR_INPUT,ULTRASONIC_ECHO};
int OUTPUT_PINS[] {L_MOTOR_DIRECTION,ULTRASONIC_TRIGGER,BOTH_MOTORS_PWM,R_MOTOR_DIRECTION,PRESS_SERVO_PWM,TRAPDOOR_SERVO_PWM,COLOR_S2,COLOR_S3};
