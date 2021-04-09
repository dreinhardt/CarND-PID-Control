#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  this->Kp = Kd_;
  this->Ki = Ki_;
  this->Kd = Kd_;
  this->p_error = 0;
  this->i_error = 0;
  this->d_error = 0;
}

void PID::UpdateError(double cte) {
  this->d_error = cte - this->p_error;  // get the difference between t0 and t-1
  this->p_error = cte;                  // set the actual cross track error variable
  this->i_error = this->i_error + cte;  // sum up all the ctes
}

double PID::TotalError() {
  return -this->Kp * this->p_error - this->Kd * this->d_error - this->Ki * this->i_error;
}