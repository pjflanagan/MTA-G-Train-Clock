
#include "Stepper.cpp"

Stepper bStepper = Stepper(D5, D6, D7, D8);
//Stepper qStepper = Stepper(D0, D1, D2, D3);

void setup()
{
	Serial.begin(115200);
	delay(20);
	Serial.println(" ==== START ==== ");
	bStepper.setDestinationMinutes(-6.14);
}

void loop()
{
	while (!bStepper.done())
	{ // this loop will be while qStepper is not done too
		bStepper.move();
		delay(2);
	}
	// determine the next time call backend
	bStepper.setDestinationMinutes(2.89);
}
