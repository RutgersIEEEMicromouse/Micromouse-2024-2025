#ifndef PIDSTRAIGHT_H
#define PIDSTRAIGHT_H
#include <Encoder.h>
#include <Arduino.h>
#include "PIDRotate.h"

class PIDStraight {

    public:
        void InputToMotor(double desiredDistance);

        const double Kp = 0.2;
        const double Ki = 0;
        const double Kd = 0;


        const double wheelDiameter = 3.9; // cm
    private:
        

};

extern PIDStraight* pidstraight_instance;
extern double trueNorth; 

#endif