#include "API.h"
#include <cstdlib>
#include <iostream>


bool API::wallFront() {
    int distance = front();
    if(distance < 100) {
        return true;
    } else {
        return false;
    }
}

bool API::wallRight() {
    int distance = right();
    if(distance < 80) {
        return true;
    } else {
        return false;
    }
}

bool API::wallLeft() {
    int distance = left();
    if(distance < 80) {
        return true;
    } else {
        return false;
    }
}


//  pidstraight_instance->InputToMotor(0,blocklength); //go 11 cm. works fine
//   pidrotate_instance->InputToMotor(-90); //left 90
double blockLength = 160;

void API::moveForward() {
    setForwardPWM(blockLength); //go 11 cm. works fine
    delay(200);
    return;
}


void API::turnRight() {
    turnTo('E'); //right 90
    delay(200);
    return;
}

void API::turnLeft() {
    turnTo('W'); //left 90
    delay(200);
    return;
}

void API::turnAround() {
    turnTo('S'); //180
    delay(200);
    return;
}
