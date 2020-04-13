
// 2048 steps per revolution
// 2ms delay between loops minimum
// 500 steps per second max speed


#include <AccelStepper.h>           // Load the AccelStepper library

#define motorPin1  D2               // IN1 pin on the ULN2003A driver
#define motorPin2  D3               // IN2 pin on the ULN2003A driver
#define motorPin3  D4               // IN3 pin on the ULN2003A driver
#define motorPin4  D5               // IN4 pin on the ULN2003A driver

int stepsPerRevolution = 2048;        // steps per revolution

/*
 * AccelStepper::FULL2WIRE (2) means: 2 wire stepper (2 pins needed). 
 * AccelStepper::FULL3WIRE (3) means: 3 wire stepper, like a harddisk motor (3 pins needed). 
 * AccelStepper::FULL4WIRE (4) means: 4 wire stepper (4 pins needed). 
 * AccelStepper::HALF3WIRE (6) means: 3 wire half stepper, like a harddisk motor (3 pins needed) 
 * AccelStepper::HALF4WIRE (8) means: 4 wire half stepper (4 pins needed) 
 *
 * AccelStepper uses AccelStepper::FULL4WIRE (4 pins needed) by default.
 */
AccelStepper stepper(AccelStepper::HALF4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {

  stepper.setMaxSpeed(200.0);      // set the max motor speed
  stepper.setSpeed(200);            // set the current speed

  stepper.moveTo(0);   // order the motor to rotate 90 degrees forward

}

void loop() {
  stepper.moveTo(90);   // order the motor to rotate 90 degrees forward
  delay(200);
  stepper.moveTo(-90);   // order the motor to rotate 90 degrees forward
}
