//test the Arduinophone object

#include "Arduinophone.h"

Arduinophone music();

void setup() {
  Serial.begin(9600);
  Serial.println("-=Arduinophone=-");
}

void loop() {
  //nothing needed here
}

void serialEvent() { //used to call object play method
  char inChar = (char)Serial.read();
  switch(inChar) {
    //NORMAL
    case 'a':
      Serial.println("low C");
      music.play(0, 1); break;
    case 's':
      Serial.println("D");
      music.play(1, 1); break;
    case 'd':
      Serial.println("E");
      music.play(2, 1); break;
    case 'f':
      Serial.println("F");
      music.play(3, 1); break;
    case 'j':
      Serial.println("G");
      music.play(4, 1); break;
    case 'k':
      Serial.println("A");
      music.play(5, 1); break;
    case 'l':
      Serial.println("B");
      music.play(6, 1); break;
    case ';': //high c
      Serial.println("high C");
      music.play(7, 1); break;
    //FLAT
    case 'z':
      Serial.println("flat low C");
      music.play(0, 2); break;
    case 'x':
      Serial.println("flat D");
      music.play(1, 2); break;
    case 'c':
      Serial.println("flat E");
      music.play(2, 2); break;
    case 'v':
      Serial.println("flat F");
      music.play(3, 2); break;
    case 'm':
      Serial.println("flat G");
      music.play(4, 2); break;
    case ',':
      Serial.println("flat A");
      music.play(5, 2); break;
    case '.':
      Serial.println("flat B");
      music.play(6, 2); break;
    case '/': //high c
      Serial.println("flat high C");
      music.play(7, 2); break;
    //DOUBLE
    case 'q':
      Serial.println("double low C");
      music.play(0, 3); break;
    case 'w':
      Serial.println("double D");
      music.play(1, 3); break;
    case 'e':
      Serial.println("double E");
      music.play(2, 3); break;
    case 'r':
      Serial.println("double F");
      music.play(3, 3); break;
    case 'u':
      Serial.println("double G");
      music.play(4, 3); break;
    case 'i':
      Serial.println("double A");
      music.play(5, 3); break;
    case 'o':
      Serial.println("double B");
      music.play(6, 3); break;
    case 'p': //high c
      Serial.println("double high C");
      music.play(7, 3); break; 
    case '1': //stop playing
      music.stop(); break; //more Arduino-like
    case '0': //start
      music.begin(); break; //more Arduino-like
  }

  //clear any keypresses received while moving
  while (Serial.available()) {
    inChar = (char)Serial.read();
  }
}

