//recieves single character commands via serial port
//commands servo and stepper motors to play bells

#include "AFMotor.h" #this is the old Adafruit library
#include <Servo.h>

Servo myservo;
AF_Stepper motor(48, 1);

//change striker timing here
int doub_wait = 1; //between strikes
int flat_wait = 150; //holds striker to bell
int user_wait = 100; //between keypresses
int pause_base = 350; //this is used to slow the position change

//starting position, top dead center
int pos = 90;
int current_note = 4;  //G
bool playing = false;

//movement matrix
int pos_displace[8][8] ={
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

void setup() {
  Serial.begin(9600);
  Serial.println("-=Arduinophone=-");
  
  pinMode(13, OUTPUT);
}

void loop() {
  //nothing needed here
}

void serialEvent() {
  char inChar = (char)Serial.read();
  switch(inChar) {
    //NORMAL
    case 'a':
      Serial.println("low C");
      go(0, 1); break;
    case 's':
      Serial.println("D");
      go(1, 1); break;
    case 'd':
      Serial.println("E");
      go(2, 1); break;
    case 'f':
      Serial.println("F");
      go(3, 1); break;
    case 'j':
      Serial.println("G");
      go(4, 1); break;
    case 'k':
      Serial.println("A");
      go(5, 1); break;
    case 'l':
      Serial.println("B");
      go(6, 1); break;
    case ';': //high c
      Serial.println("high C");
      go(7, 1); break;
    //FLAT
    case 'z':
      Serial.println("flat low C");
      go(0, 2); break;
    case 'x':
      Serial.println("flat D");
      go(1, 2); break;
    case 'c':
      Serial.println("flat E");
      go(2, 2); break;
    case 'v':
      Serial.println("flat F");
      go(3, 2); break;
    case 'm':
      Serial.println("flat G");
      go(4, 2); break;
    case ',':
      Serial.println("flat A");
      go(5, 2); break;
    case '.':
      Serial.println("flat B");
      go(6, 2); break;
    case '/': //high c
      Serial.println("flat high C");
      go(7, 2); break;
    //DOUBLE
    case 'q':
      Serial.println("double low C");
      go(0, 3); break;
    case 'w':
      Serial.println("double D");
      go(1, 3); break;
    case 'e':
      Serial.println("double E");
      go(2, 3); break;
    case 'r':
      Serial.println("double F");
      go(3, 3); break;
    case 'u':
      Serial.println("double G");
      go(4, 3); break;
    case 'i':
      Serial.println("double A");
      go(5, 3); break;
    case 'o':
      Serial.println("double B");
      go(6, 3); break;
    case 'p': //high c
      Serial.println("double high C");
      go(7, 3); break; 
    case '1': //stop playing
      ending(); break;
    case '0': //start
      start(); break;
    default:
      pos = pos;
  }

  //clear any keypresses received while moving
  while (Serial.available()) {
    inChar = (char)Serial.read();
  }
}

void go (int to, int mode) {
  if (playing) { //only move if started
    digitalWrite(13, HIGH);
    
    if (to != current_note) {
      int inc = pos_displace[to][current_note];
      int next = pos + inc;
      int by = (inc >= 0 ? 1 : -1);
      int pause = pause_base / abs(inc);
      for (pos; pos != next; pos += by) {
        myservo.write(pos);
        delay(pause); //takes less time per itteration on longer jumps
      }
      delay(15);
      current_note = to;
    }

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
  
    delay(user_wait); //used to slow if user holds down a key
    digitalWrite(13, LOW);
  }
}

void ending() {
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

void start() {
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

