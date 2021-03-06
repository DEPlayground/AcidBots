/*
  AcidBot Prototype (Line Tracking) - gamma platform
  Copyright (C) 2016 - Acidhub <contact@acidhub.click>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

  =======================================================================

*/

#include <Arduino.h> //Now a PlatformIO project :)

#define LSensorLeft    8 // Left sensor input
#define LSensorMiddle  7  // Middle sensor input
#define LSensorRight   6  // Right sensor input

unsigned char LSL;        // Left sensor status
unsigned char LSM;        // Middle sensor status
unsigned char LSR;        // Right sensor status

#define M1 12            // Right wheel
#define M2 13            // Left wheel
#define E1 3             // Right wheel speed control
#define E2 11            // Left wheel speed control

void sensorConfig(void) {
    pinMode(LSensorLeft,INPUT);
    pinMode(LSensorMiddle,INPUT);
    pinMode(LSensorRight,INPUT);
}

void sensorScan(void) {
    LSL = digitalRead(LSensorLeft);
    LSM = digitalRead(LSensorMiddle);
    LSR = digitalRead(LSensorRight);
}

void motorControlConfig(void) { // Motor pinout config (Shield IO)
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
}

void forward(void) {       // Move forward
    digitalWrite(M1, LOW);   // Both left and right wheel move forward
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

void backward(void) {          // Move backward
    digitalWrite(M1, HIGH);  // Both left and right wheel move backward
    digitalWrite(M2, LOW);
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

void right(void) {         // Turn right
    digitalWrite(M1, HIGH);  // Left wheel moves forward
    digitalWrite(M2, HIGH);  // Right wheel moves backward
    analogWrite(E1, 255);
    analogWrite(E2, 150);
}

void left(void) {          // Turn left
    digitalWrite(M1, LOW);   // Left wheel moves backward
    digitalWrite(M2, LOW);   // Right wheel moves forward
    analogWrite(E1, 150);
    analogWrite(E2, 255);
}

void stop_(void) {         // Stop
    analogWrite(E1, 0);      // Useless set motor direction
    analogWrite(E2, 0);      // Both left and right wheel stop
}

void setup() {
    sensorConfig();        // Sensors init (Shield IO)
    motorControlConfig();  // Motor init (Shield IO)
    stop_();
}

void loop() {
    sensorScan();
    if((LSL==1&&LSM==1&&LSR==1)||(LSL==1&&LSM==1&&LSR==0)||(LSL==0&&LSM==1&&LSR==1)||(LSL==0&&LSM==1&&LSR==0)) {
        forward();
    }
    if((LSL==0&&LSM==0&&LSR==0)||(LSL==0&&LSM==0&&LSR==1)) {
        left();
    }
    if(LSL==1&&LSM==0&&LSR==0) {
        right();
    }
}
