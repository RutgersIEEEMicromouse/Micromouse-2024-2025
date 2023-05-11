#ifndef API_H
#define API_H
#pragma once


#include "..\tof.h"
#include "..\PIDRotate.h"
#include "..\PIDStraight.h"

#include <string>

class API {

#define blockLength 10

public:
    static bool wallFront();
    static bool wallRight();
    static bool wallLeft();

    static void moveForward();
    static void turnRight();
    static void turnLeft();
};
#endif