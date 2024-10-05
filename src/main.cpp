#include "lib/imu.h"
#include "lib/distance_sensor.h"
#include "lib/motors.h"
#include "lib/pidRotate.h"
#include "lib/pidStraight.h"
#include "../src/pathfinding/API.h"
#include "../src/pathfinding/Flood.h"
#include "../src/pathfinding/simAPI.h"
#include "../src/pathfinding/labyrinth.h"



VL53L1X sensor;
int modePin = 12;  // LED connected to digital pin 13
int val = 0;      // variable to store the read value


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
  Serial.println("Hello world");

  val = digitalRead(modePin);   // read the input pin

  if(val == 0) {
    runMaze('c');
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    labyrinth();
  }

  

}

void loop()
{
  // delay(500);
  
  // Serial.println(digitalRead(modePin));
  // Serial.println(digitalRead(memory_button));
  // Serial.println(digitalRead(memory_switch));
}