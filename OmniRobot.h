// OmniRobot.h
#ifndef OmniRobot_h
#define OmniRobot_h

#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"

class OmniRobot {
private:
    PCF8574 pcf;
    volatile int e1, e2, e3, e4;
    #define M_PI 3.14159265358979323846

    void updateEncoders() {
        if (pcf.readEncoderValue(P7, P0)) e1++;
        if (pcf.readEncoderValue(P6, P1)) e2++;
        if (pcf.readEncoderValue(P5, P2)) e3++;
        if (pcf.readEncoderValue(P4, P3)) e4++;
    }

public:
    OmniRobot(uint8_t pcf_address = 0x20) : pcf(pcf_address), e1(0), e2(0), e3(0), e4(0) {}

    void begin() {
        // Initialize motor control pins
        for (int i = 4; i <= 11; i++) {
            pinMode(i, OUTPUT);
        }
        
        // Initialize encoder pins
        pcf.pinMode(P0, INPUT);
        pcf.pinMode(P1, INPUT);
        pcf.pinMode(P2, INPUT);
        pcf.pinMode(P3, INPUT);
        pcf.pinMode(P4, INPUT);
        pcf.pinMode(P5, INPUT);
        pcf.pinMode(P6, INPUT);
        pcf.pinMode(P7, INPUT);
        
        // Setup encoders
        pcf.encoder(P7, P0);
        pcf.encoder(P6, P1);
        pcf.encoder(P5, P2);
        pcf.encoder(P4, P3);
    }

    void moveTimed(long duration, int va = 0, int vb = 0, int vc = 0, int vd = 0, float k = 1) {
        e1 = e2 = e3 = e4 = 0;
        long startTime = millis();
        double i1 = va, i2 = vb, i3 = vc, i4 = vd;
        
        // Disable PID for stopped motors
        if (va == 0) e1 = 1000000;
        if (vb == 0) e2 = 10000000;
        if (vc == 0) e3 = 10000000;
        if (vd == 0) e4 = 1000000;
        
        while (millis() - startTime < duration) {
            updateEncoders();
            float time = millis() / 1000.0;
            i1 = time * va * k;
            i2 = time * vb * k;
            i3 = time * vc * k;
            i4 = time * vd * k;
            
            int speed1 = i1 - e1;
            int speed2 = i2 - e2;
            int speed3 = i3 - e3;
            int speed4 = i4 - e4;
            
            analogWrite(5, constrain(speed1 + va, 0, 255));
            analogWrite(9, constrain(speed2 + vb, 0, 255));
            analogWrite(6, constrain(speed3 + vc, 0, 255));
            analogWrite(10, constrain(speed4 + vd, 0, 255));
        }
        stop();
    }

    void moveOmni3(int angle, long duration, float speed = 1) {
        int va = speed * cos((150 - angle) * M_PI / 180);
        int vc = speed * cos((30 - angle) * M_PI / 180);
        int vb = speed * cos((270 - angle) * M_PI / 180);
        
        digitalWrite(8, vc > 0);
        digitalWrite(4, va > 0);
        digitalWrite(7, vb > 0);
        
        moveTimed(duration, va, vb, vc, 0, speed);
    }

    void moveOmni4(int angle, long duration, float speed = 1) {
        int va = speed * cos(angle * M_PI / 180);
        int vb = speed * cos((90 - angle) * M_PI / 180);
        int vc = speed * cos((180 - angle) * M_PI / 180);
        int vd = speed * cos((270 - angle) * M_PI / 180);
        
        digitalWrite(4, va < 0);
        digitalWrite(8, vb < 0);
        digitalWrite(7, vc < 0);
        digitalWrite(11, vd < 0);
        
        moveTimed(duration, va, vb, vc, vd, speed);
    }

    void moveMecanumFB(int speed, bool reverse = false) {
        digitalWrite(4, reverse);
        digitalWrite(8, reverse);
        digitalWrite(7, reverse);
        digitalWrite(11, reverse);
        
        analogWrite(5, speed);
        analogWrite(6, speed);
        analogWrite(9, speed);
        analogWrite(10, speed);
    }

    void moveMecanumRL(bool right, int speed) {
        digitalWrite(4, !right);
        digitalWrite(7, right);
        digitalWrite(8, right);
        digitalWrite(11, !right);
        
        analogWrite(5, speed);
        analogWrite(6, speed);
        analogWrite(9, speed);
        analogWrite(10, speed);
    }

    void stop() {
        analogWrite(6, 0);
        analogWrite(5, 0);
        analogWrite(9, 0);
        analogWrite(10, 0);
        delay(500);
    }
};

#endif