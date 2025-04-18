#include "OmniRobot.h"

OmniRobot robot;

void setup() {
  Serial.begin(9600);
  robot.begin();
}

void loop() {
  // Движение по парралелограмму
  robot.moveOmni4(45, 1000);
  robot.moveOmni4(90,2000);
  robot.moveOmni4(225,1000);//180 (вниз) + 45 (влевво) 
  robot.moveOmni4(270,1000);
  robot.stop();//Остановка
  //Движение по трапеции
  robot.moveOmni4(45,1000);
  robot.moveOmni4(90,1000);
  robot.moveOmni4(135,1000);//90+45
  robot.moveOmni4(270,2000);
  robot.stop();//Остановка
  exit(0);//Выход из программы
}