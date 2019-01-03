//Arduinophone Library

#include <Arduino.h>
#include "AFMotor.h" #Please use version included here
#include <Servo.h>

#ifndef _Arduinophone_h_
#define _Arduinophone_h_

class Arduinophone {
public:
  Arduinophone();

  void begin ();
  void stop ();

  //note 1 - 8 : mode 1=normal, 2 = flat, 3=double
  void play (int note, int mode);
  
private:
  Servo myservo; //travel arm
  AF_Stepper motor; //striker, uses new zero arg constructor

  //change striker timing here
  int doub_wait = 1; //between strikes
  int flat_wait = 150; //holds striker to bell

  //starting position, top dead center
  int pos = 90;
  int current_note = 4; //G
  bool playing = false; //initialize as stopped

  //movement matrix
  int pos_displace[8][8] = {
    //~140  125   115   100   90    70    55    45
    // lc    d     e     f     g     a     b     hc   from
    {   0,   15,   25,   40,   52,   70,   85,   87}, // lc    to
    { -15,    0,   14,   26,   40,   50,   70,   80}, // d
    { -25,  -15,    0,   12,   25,   40,   50,   65}, // e
    { -40,  -25,  -12,    0,   13,   25,   40,   45}, // f
    { -59,  -40,  -25,  -15,    0,   15,   25,   42}, // g
    { -70,  -50,  -40,  -25,  -15,    0,   15,   20}, // a
    { -85,  -75,  -50,  -40,  -25,  -15,    0,   10}, // b
    { -88,  -81,  -70,  -45,  -35,  -20,  -10,    0}  // hc
  };
};

#endif
