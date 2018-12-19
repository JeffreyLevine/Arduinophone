# Arduinophone
Arduino Powered Robotic Bell Playing Doorbell  
For code to play tunes on the [Arduinophone](https://www.youtube.com/watch?time_continue=1&v=WLKqLVUCKDU)  

### Sketch
The Arduino sketch enables the user to play notes via a serial console.  
  
Please note that if you use the Serial Monitor in the Arduino IDE you have to press Send after each key. I recommend using a Terminal Emulator program, which enables the user to play notes like a piano.

![keymap](https://github.com/JeffreyLevine/Arduinophone/blob/master/Docs/keymap.png)  
the red letters are playable notes

### Play_Song.py
This Python script allows the user to send long sequences of notes stored in a text file. Script requires 1 argument, the name of the file to be sent.

### FILE FORMAT
:First line is comma separated notes  
  
"+A" doulbe  
"A" normal  
"-A" flat  
"LC" low C  
"HC" high C  
Notes in order: LC D E F G A B HC  
"***" start playing notes  
"NNN" end, stop playing and release servo and stepper  
  
:Second line is comma separated delays (in seconds)  

This is forms a 2 line CSV file
