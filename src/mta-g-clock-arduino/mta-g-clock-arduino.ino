
#ifndef MTA_G_CLOCK_API
#define MTA_G_CLOCK_API

#include "API.h"

#include "Stepper.cpp"

// declare our steppers here
Stepper bStepper = Stepper(D5, D6, D7, D8);
Stepper qStepper = Stepper(D0, D1, D2, D3);

// when millis() is greater than this, it is time to make the next request
int g_next_request_time = 0;

// set this to millis() when you move the motors
int g_last_move_time = 0;

// time until next queens bound and brooklyn bound trains
float qb, bb = 20;

void setup()
{
  Serial.begin(115200); // can be removed after debugging
  Serial.println(" ===== Start MTA Clock ===== ");
  bStepper.setDestinationMinutes(0);
  qStepper.setDestinationMinutes(0);
  init_wifi();
}

void loop()
{

  if (millis() > g_next_request_time)
  {
    // if it is past the next request time, make a request
    String response = send_request();
    Serial.print("Response: ");
    Serial.println(response);
    qb = get_time_for_train('Q', &response);
    bb = get_time_for_train('B', &response);

    // set the next time to make a request to 3/4 of the shortest train time
    float request_delay = (qb < bb) ? qb : bb;
    request_delay = request_delay * 60 * 1000;
    g_next_request_time = millis() + int(request_delay) * 3 / 4;
  
    Serial.print("Next request time: ");
    Serial.println(g_next_request_time);
  }
  else
  {
    // otherwise calculate the new wait time by subtracting how long it's been since the last request
    float time_since_last_move_in_minutes = float((millis() - g_last_move_time)) / float(1000 * 60);
    Serial.print("Time since last move: ");
    Serial.println(time_since_last_move_in_minutes);
    qb = (qb - time_since_last_move_in_minutes <= 0) ? 0 : qb - time_since_last_move_in_minutes;
    bb = (bb - time_since_last_move_in_minutes <= 0) ? 0 : bb - time_since_last_move_in_minutes;
  }

  Serial.print("Queens: ");
  Serial.println(qb);
  Serial.print("Brooklyn: ");
  Serial.println(bb);

  // // set the motors
   qStepper.setDestinationMinutes(qb);
   bStepper.setDestinationMinutes(bb);

  g_last_move_time = millis();
  // // move the motors, this step takes time, so we will need to account for it when moving them the next time
  while (!qStepper.done() && !bStepper.done())
  {
    qStepper.move();
    bStepper.move();
    delay(2);
  }


  //  TODO: calculate how long it took to move and see how long we need to delay int time_to_move = millis() - last_move_time;
  // delay 10 seconds
  delay(1000 * 10);
}

#endif
