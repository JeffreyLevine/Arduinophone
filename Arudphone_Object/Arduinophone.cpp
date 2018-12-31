#include "Arduinophone.h"

Arduinophone::Arduinophone () { //Constructor
  pinMode(13, OUTPUT); //used for test light

  motor = AF_Stepper(48, 1); //set stepper
}

void Arduinophone::play(int to, int mode) {
  if (playing) { //only move if started
    digitalWrite(13, HIGH); //test light
    
    if (to != current_note) { //travel arm
      int next = pos + pos_displace[to][current_note];

      myservo.write(next); //jump directly to destination
      pos = next; //servo
      
      current_note = to; //note
    }

    delay(250); //wait for travel arm

    switch (mode) { //striker
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
} //4 notes a second max

void Arduinophone::stop() {
  if (playing) { //only stop if started
    playing = false;
    
    //move striker back down to rail
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
    
    //disable motor and servo
    motor.release();
    myservo.write(90);
    delay(200); //make sure travel arm is centered
    myservo.detach();
  
    pos = 90;
    current_note = 4;  //G
  
    Serial.println("Stop Playing");
  }
}

void Arduinophone::begin() {
  if (!playing) { //only start if stopped
    playing = true;

    //enable motor and servo
    myservo.attach(9);
    motor.setSpeed(100);

    //move striker into position
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
}

