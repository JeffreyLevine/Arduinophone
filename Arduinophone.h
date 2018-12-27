//asdf

#ifndef _AFMotor_h_
#define _AFMotor_h_

#include <Arduino.h>
#include "AFMotor.h" #this is the old Adafruit library
#include <Servo.h>

class Arduinophone {
public:
  Arduinophone();

  void begin ();
  void stop ();

  void play (int note, int mode);
  
private:
  Servo myservo;
  AF_Stepper motor;

  //change striker timing here
  int doub_wait = 1; //between strikes
  int flat_wait = 150; //holds striker to bell
  int user_wait = 100; //between keypresses
  int pause_base = 10000; //this is used to slow the position change

  //starting position, top dead center
  int pos = 90;
  int current_note = 4;  //G
  bool playing = false;

  //movement matrix
  int pos_displace[8][8];
};

#endif
