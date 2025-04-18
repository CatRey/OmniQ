#include "OmniRobot.h"

OmniRobot robot;

void setup() {
  Serial.begin(9600);
  robot.begin();
}

void loop() {
  //Движение по прямоугольнику 5 раз с разными скоростями
  for (int speed = 100; speed < 230; speed += 26) {
    robot.moveMecanumFB(speed);
    robot.moveMecanumRL(true, speed);
    robot.moveMecanumFB(speed, true);
    robot.moveMecanumRL(false, speed);
  }
  exit(0);  //Выход из программы
}