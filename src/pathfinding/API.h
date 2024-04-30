
#ifndef API_H
#define API_H
#pragma once


#include "..\src\lib\distance_sensor.h"
#include "..\src\lib\pidRotate.h"
#include "..\src\lib\pidStraight.h"
#include "..\src\lib\IMU.h"

#include <string>

class API {


public:
    static bool wallFront();
    static bool wallRight();
    static bool wallLeft();

    static void moveForward();
    static void turnRight();
    static void turnLeft();
    static void turnAround();
};
#endif
