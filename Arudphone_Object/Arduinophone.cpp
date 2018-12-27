#include "Arduinophone.h"

Arduinophone::Arduinophone () {
  //Constructor
  pinMode(13, OUTPUT);
    pos_displace[8][8] = {
  //~140  125   115   100   90    70    55    45
  // lc    d     e     f     g     a     b     hc   from
     0,   15,   25,   40,   52,   70,   85,   87, // lc    to
   -15,    0,   14,   26,   40,   50,   70,   80, // d
   -25,  -15,    0,   12,   25,   40,   50,   65, // e
   -40,  -25,  -12,    0,   13,   25,   40,   45, // f
   -59,  -40,  -25,  -15,    0,   15,   25,   42, // g
   -70,  -50,  -40,  -25,  -15,    0,   15,   20, // a
   -85,  -75,  -50,  -40,  -25,  -15,    0,   10, // b
   -88,  -81,  -70,  -45,  -35,  -20,  -10,    0  // hc
  };

  motor = new AF_Stepper(48, 1);
}

void Arduinophone::play(int to, int mode) {
  if (playing) { //only move if started
    digitalWrite(13, HIGH);
    
    if (to != current_note) {
      int inc = pos_displace[to][current_note];
      int next = pos + inc;

      myservo.write(next);
      pos = next;
      
      current_note = to;
    }

    delay(250);

    switch (mode) {
      case 1: //normal
        motor.step(5, FORWARD, DOUBLE);
        motor.step(5, BACKWARD, DOUBLE);
        break;
      case 2: //flat
        motor.step(5, FORWARD, DOUBLE);
        delay(flat_wait); //keeps hammer on the bell
        motor.step(5, BACKWARD, DOUBLE);
        break;
      case 3: //double
        motor.step(5, FORWARD, DOUBLE);
        motor.step(5, BACKWARD, DOUBLE);
        delay(doub_wait);
        motor.step(5, FORWARD, DOUBLE);
        motor.step(5, BACKWARD, DOUBLE);
        break;
    }

    digitalWrite(13, LOW);
  }
}

void Arduinophone::stop() {
  playing = false;
  
  //move back
  motor.step(4, BACKWARD, DOUBLE);
  delay(200);
  motor.step(4, BACKWARD, DOUBLE);
  delay(200);
  motor.step(4, BACKWARD, DOUBLE);
  delay(200);
  motor.step(3, BACKWARD, DOUBLE);
  delay(200);
  motor.step(3, BACKWARD, DOUBLE);
  delay(200);
  
  //disengauge motor and servo
  motor.release();
  myservo.write(90);
  delay(200);
  myservo.detach();

  pos = 90;
  current_note = 4;  //G

  Serial.println("Stop Playing");
}

void Arduinophone::begin() {
  playing = true;
  
  myservo.attach(9);

  motor.setSpeed(100);

  motor.step(3, FORWARD, DOUBLE);
  delay(200);
  motor.step(3, FORWARD, DOUBLE);
  delay(200);
  motor.step(4, FORWARD, DOUBLE);
  delay(200);
  motor.step(4, FORWARD, DOUBLE);
  delay(200);
  motor.step(4, FORWARD, DOUBLE);
  delay(200);

  Serial.println("Start Playing");
}

