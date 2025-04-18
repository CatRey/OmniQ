#include "OmniRobot.h"

OmniRobot robot;

void setup() {
  Serial.begin(9600);
  robot.begin();
}

void loop() {
  // Движение по кругу
  for (int angle = 0; angle < 360; angle += 15) {
    robot.moveOmni3(angle, 100);  //Движение на angle в течение 100 милисекунд
  }
  robot.stop();//Остановка после проезда круга
}