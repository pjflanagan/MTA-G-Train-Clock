
#ifndef STEPPER_CPP
#define STEPPER_CPP

#include <Arduino.h>

const int STEPS_PER_REV = 2048;
const int ROTATIONS_PER_MINUTE_REPRESENTATION = 4;

class Stepper
{
  public:
    Stepper(int p1, int p2, int p3, int p4)
    {
      pinMode(p1, OUTPUT);
      pinMode(p2, OUTPUT);
      pinMode(p3, OUTPUT);
      pinMode(p4, OUTPUT);
      this->_p1 = p1;
      this->_p2 = p2;
      this->_p3 = p3;
      this->_p4 = p4;
    }

    void setDestinationMinutes(float minutes)
    {
      // translate minutes to steps
      this->_destination = int(minutes * STEPS_PER_REV * ROTATIONS_PER_MINUTE_REPRESENTATION);
    }

    void move()
    {
      // if delta is not 0, move one step
      if (!this->done())
      {
        this->_oneStep();
      }
      else
      {
        this->_noStep();
      }
    }

    bool done()
    {
      // get in the range of current
      return (this->_current >= this->_destination - 10 && this->_current <= this->_destination + 10);
    }

  private:
    int _getDirection()
    {
      int delta = this->_destination - this->_current;
      return (delta < 0) ? -1 : 1;
    }

    void _noStep()
    {
      digitalWrite(this->_p1, LOW);
      digitalWrite(this->_p2, LOW);
      digitalWrite(this->_p3, LOW);
      digitalWrite(this->_p4, LOW);
    }

    void _oneStep()
    {
      int dir = this->_getDirection();
      switch (this->_next_move)
      {
        case 0:
          digitalWrite(this->_p1, LOW);
          digitalWrite(this->_p2, LOW);
          digitalWrite(this->_p3, LOW);
          digitalWrite(this->_p4, HIGH);
          break;
        case 1:
          digitalWrite(this->_p1, LOW);
          digitalWrite(this->_p2, LOW);
          digitalWrite(this->_p3, HIGH);
          digitalWrite(this->_p4, HIGH);
          break;
        case 2:
          digitalWrite(this->_p1, LOW);
          digitalWrite(this->_p2, LOW);
          digitalWrite(this->_p3, HIGH);
          digitalWrite(this->_p4, LOW);
          break;
        case 3:
          digitalWrite(this->_p1, LOW);
          digitalWrite(this->_p2, HIGH);
          digitalWrite(this->_p3, HIGH);
          digitalWrite(this->_p4, LOW);
          break;
        case 4:
          digitalWrite(this->_p1, LOW);
          digitalWrite(this->_p2, HIGH);
          digitalWrite(this->_p3, LOW);
          digitalWrite(this->_p4, LOW);
          break;
        case 5:
          digitalWrite(this->_p1, HIGH);
          digitalWrite(this->_p2, HIGH);
          digitalWrite(this->_p3, LOW);
          digitalWrite(this->_p4, LOW);
          break;
        case 6:
          digitalWrite(this->_p1, HIGH);
          digitalWrite(this->_p2, LOW);
          digitalWrite(this->_p3, LOW);
          digitalWrite(this->_p4, LOW);
          break;
        case 7:
          digitalWrite(this->_p1, HIGH);
          digitalWrite(this->_p2, LOW);
          digitalWrite(this->_p3, LOW);
          digitalWrite(this->_p4, HIGH);
          break;
        default:
          digitalWrite(this->_p1, LOW);
          digitalWrite(this->_p2, LOW);
          digitalWrite(this->_p3, LOW);
          digitalWrite(this->_p4, LOW);
          break;
      }
      this->_setNextMove(dir); // set the next move
      this->_current += dir;	 // subtract one from the delta
    }

    void _setNextMove(int dir)
    {
      // move in the direction
      this->_next_move += dir;
      if (this->_next_move > 7)
      {
        this->_next_move = 0;
      }
      else if (this->_next_move < 0)
      {
        this->_next_move = 7;
      }
    }

    // stepper wiring
    int _p1, _p2, _p3, _p4;
    int _next_move = 0; // [0, 7]

    // calculated on position set
    int _current = 0;	  // steps away from destination
    int _destination = 0; // steps
};

#endif
