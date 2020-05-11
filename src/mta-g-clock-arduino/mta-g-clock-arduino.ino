
#include "API.cpp"

int next_request_time = 0;
float qb, bb = 20;

void setup()
{
  init_wifi();
}

void loop()
{
  int now = millis();

  if (now > next_request_time) {
    // if it is past the next request time, make a request
    String response = send_request();
    qb = get_time_for_train('Q', &response);
    bb = get_time_for_train('B', &response);
  } else {
    // otherwise subtract half a minute
    qb = (qb <= 1) ? 0 : qb - .5;
    bb = (bb <= 1) ? 0 : bb - .5;
  }

  // TODO: move the motors here
  Serial.print("Queens: ");
  Serial.println(qb);
  Serial.print("Brooklyn: ");
  Serial.println(bb);

  // set the next time to make a request to 3/4 of the shortest train time
  float delay_t = (qb < bb) ? qb : bb;
  delay_t = delay_t * 60 * 1000;
  next_request_time = now + int(delay_t) * 3 / 4;

  // delay 30 seconds
  delay(1000 * 30);
}
