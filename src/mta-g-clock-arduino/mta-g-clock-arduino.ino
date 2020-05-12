
#ifndef MTA_G_CLOCK_API
#define MTA_G_CLOCK_API

#include "API.h"

// when millis() is greater than this, it is time to make the next request
int next_request_time = 0;

// time until next queens bound and brooklyn bound trains
float qb, bb = 20;

void setup()
{
  Serial.begin(115200); // can be removed after debugging
  init_wifi();
}

void loop()
{
  int now = millis();

  if (now > next_request_time)
  {
    // if it is past the next request time, make a request
    String response = send_request();
    qb = get_time_for_train('Q', &response);
    bb = get_time_for_train('B', &response);
  }
  else
  {
    // otherwise subtract half a minute
    qb = (qb <= 1) ? 0 : qb - .5;
    bb = (bb <= 1) ? 0 : bb - .5;
  }

  // TODO: move the motors here
  Serial.print("Queens: ");
  Serial.println(qb);
  Serial.print("Brooklyn: ");
  Serial.println(bb);

  // // set the motors
  // qStepper.setDestinationMinutes(qb);
  // bStepper.setDestinationMinutes(bb);

  // // move the motors
  // while (!qStepper.done() && !bStepper.done())
  // {
  // 	qStepper.move();
  // 	bStepper.move();
  // 	delay(2);
  // }

  // set the next time to make a request to 3/4 of the shortest train time
  float delay_t = (qb < bb) ? qb : bb;
  delay_t = delay_t * 60 * 1000;
  next_request_time = now + int(delay_t) * 3 / 4;

  // delay 30 seconds
  // TODO: this is wrong because moving takes time
  delay(1000 * 30);
}

#endif
