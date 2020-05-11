
// 2048 steps per revolution
// 2ms delay between loops minimum
// 500 steps per second max speed


#include <AccelStepper.h>           // Load the AccelStepper library

#define IN1  D5               // IN1 pin on the ULN2003A driver
#define IN2  D6               // IN2 pin on the ULN2003A driver
#define IN3  D7               // IN3 pin on the ULN2003A driver
#define IN4  D8               // IN4 pin on the ULN2003A driver

const int STEPS_PER_REV = 2048;        // steps per revolution

/*
   AccelStepper::FULL2WIRE (2) means: 2 wire stepper (2 pins needed).
   AccelStepper::FULL3WIRE (3) means: 3 wire stepper, like a harddisk motor (3 pins needed).
   AccelStepper::FULL4WIRE (4) means: 4 wire stepper (4 pins needed).
   AccelStepper::HALF3WIRE (6) means: 3 wire half stepper, like a harddisk motor (3 pins needed)
   AccelStepper::HALF4WIRE (8) means: 4 wire half stepper (4 pins needed)

   AccelStepper uses AccelStepper::FULL4WIRE (4 pins needed) by default.
*/
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN2, IN3, IN4);

int MIN_SPEED = 300;
int pos = 512 * 4;
int dir = -1;

void setup() {
  Serial.begin(115200); // can be removed after debugging

  //  stepper.setMaxSpeed(512);
  stepper.setAcceleration(100);
  stepper.moveTo(dir);
  stepper.setSpeed(MIN_SPEED);
}

void loop() {
  Serial.print(stepper.speed());
  Serial.print("s : ");
  Serial.print(stepper.currentPosition());
  Serial.print("cp -> ");
  Serial.print(stepper.targetPosition());
  Serial.print("tp = ");
  Serial.print(stepper.distanceToGo());
  Serial.print("d\n");

  // change direction when the stepper reaches the target position
  if (stepper.distanceToGo() == 0) {
    dir = -dir;
    stepper.moveTo(pos * dir);
    stepper.setSpeed(MIN_SPEED * dir);
  }
  stepper.run();
  delay(2);
}
