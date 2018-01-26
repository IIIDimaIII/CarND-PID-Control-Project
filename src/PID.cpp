#include "PID.h"
#include <iostream>
#include <cmath>


using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi) {
Kp = Kpi;
Ki = Kii;
Kd = Kdi;
p_error = 0;
i_error = 0;
d_error = 0;

}

void PID::UpdateError(double cte) {
d_error = (cte - p_error) / 1.;
p_error = cte;
i_error += cte;
}

double PID::TotalError() { 
    return -Kp * p_error +
           -Ki * i_error +
           -Kd * d_error; 
}

