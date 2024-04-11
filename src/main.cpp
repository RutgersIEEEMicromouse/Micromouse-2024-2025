#include "lib/imu.h"
#include "lib/distance_sensor.h"
#include "lib/motors.h"
#include "lib/pidRotate.h"
#include "lib/pidStraight.h"


VL53L1X sensor;

void setup()
{
  imuSetup();
  sensorInit();
  motorSetup();

}

void loop()
{
//turnTo('W');
  // Serial.print(sensor.read());
  // if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  // Serial.println();
  // delay(500);
  // Serial.println(front());
  // Serial.println(left());
  // Serial.println(right());
  // Serial.print("angle(): ");
  // Serial.println(angle());
  // setLeftPWM(100);
  // setRightPWM(100);
  // Serial.print("angle(): ");
  // Serial.println(angle());
/*  turnTo('W');

  delay(1000);
  turnTo('S');
  // Serial.print("angle(): ");
  // Serial.println(angle());
  delay(1000);
  turnTo('E');
  // Serial.print("angle(): ");
  // Serial.println(angle());
  delay(1000);
  turnTo('N');
  delay(1000);*/
  setForwardPWM(160);
  delay(5000);

}