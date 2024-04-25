#include "lib/imu.h"
#include "lib/distance_sensor.h"
#include "lib/motors.h"
#include "lib/pidRotate.h"
#include "lib/pidStraight.h"
#include "../src/pathfinding/API.h"
#include "../src/pathfinding/Flood.h"
#include "../src/pathfinding/simAPI.h"


VL53L1X sensor;

void setup()
{
  imuSetup();
  sensorInit();
  motorSetup();
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  setForwardPWM(50);
  delay(500);
  initialize();
}

void loop()
{

  // delay(1000);
  // //setForwardPWM(160);
  // delay(2000);  
  runMaze('c');

}