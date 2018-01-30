/* Super Mario Bros. Overworld Theme with 3-way Polyphony
 * Modified by Ricardo Moreno
 * https://github.com/rmorenojr/ElegooTutorial
 * 1/26/2018
 * 
 * Original:
 * Arduino Music! Super Mario Bros. Overworld Theme (old version)
 * Ignacio Castillo Álvarez
 * https://pastebin.com/AKR5VL87
 * 
 * Tone.h Library
 * Properties
 *     No properties.
 * Methods
 *     begin(pin) - prepares a pin for playing a tone.
 *     isPlaying() - returns true if tone is playing, false if not.
 *     play(frequency[,duration]) - play a tone. 
 *       - frequency is in Hertz, and the duration is in milliseconds.
 *       - duration is optional. If duration is not given, tone will 
 *         play continuously until stop() is called.
 *       - play() is non-blocking. Once called, play() will return 
 *         immediately. If duration is given, the tone will play for 
 *         that amount of time, and then stop automatically.
 *     stop() - stop playing a tone.
 *     
 * Constants:   Musical Notes
 *   Constant Name   Frequency (Hz)   Constant Name   Frequency (Hz) 
 *      NOTE_B0           31              NOTE_C5           523
 *      NOTE_C1           33              NOTE_CS5          554
 *      NOTE_CS1          35              NOTE_D5           587
 *      NOTE_D1           37              NOTE_DS5          622
 *      NOTE_DS1          39              NOTE_E5           659
 *      NOTE_E1           41              NOTE_F5           698
 *      NOTE_F1           44              NOTE_FS5          740
 *      NOTE_FS1          46              NOTE_G5           784
 *      NOTE_G1           49              NOTE_GS5          831
 *      NOTE_GS1          52              NOTE_A5           880
 *      NOTE_A1           55              NOTE_AS5          932
 *      NOTE_AS1          58              NOTE_B5           988
 *      NOTE_B1           62              NOTE_C6          1047
 *      NOTE_C2           65              NOTE_CS6         1109
 *      NOTE_CS2          69              NOTE_D6          1175
 *      NOTE_D2           73              NOTE_DS6         1245
 *      NOTE_DS2          78              NOTE_E6          1319
 *      NOTE_E2           82              NOTE_F6          1397
 *      NOTE_F2           87              NOTE_FS6         1480
 *      NOTE_FS2          93              NOTE_G6          1568
 *      NOTE_G2           98              NOTE_GS6         1661
 *      NOTE_GS2          104             NOTE_A6          1760
 *      NOTE_A2           110             NOTE_AS6         1865
 *      NOTE_AS2          117             NOTE_B6          1976
 *      NOTE_B2           123             NOTE_C7          2093
 *      NOTE_C3           131             NOTE_CS7         2217
 *      NOTE_CS3          139             NOTE_D7          2349
 *      NOTE_D3           147             NOTE_DS7         2489
 *      NOTE_DS3          156             NOTE_E7          2637
 *      NOTE_E3           165             NOTE_F7          2794
 *      NOTE_F3           175             NOTE_FS7         2960
 *      NOTE_FS3          185             NOTE_G7          3136
 *      NOTE_G3           196             NOTE_GS7         3322
 *      NOTE_GS3          208             NOTE_A7          3520
 *      NOTE_A3           220             NOTE_AS7         3729
 *      NOTE_AS3          233             NOTE_B7          3951
 *      NOTE_B3           247             NOTE_C8          4186
 *      NOTE_C4           262             NOTE_CS8         4435
 *      NOTE_CS4          277             NOTE_D8          4699
 *      NOTE_D4           294             NOTE_DS8         4978
 *      NOTE_DS4          311
 *      NOTE_E4           330
 *      NOTE_F4           349
 *      NOTE_FS4          370
 *      NOTE_G4           392
 *      NOTE_GS4          415
 *      NOTE_A4           440
 *      NOTE_AS4          466
 *      NOTE_B4           494
 */ 
 
#include <Tone.h>

//Note Atmega328 can only have three Tone objects at a time
Tone left;
Tone right;
Tone center;
// If you instantiate 3 Tone classes, the delay function is disabled and it will crash your Arduino,
// it just freezes - nothing permantent

//Global Constants
// Timing
// quarter note duration = 100 beats per minute
const int t = 75;        
const int tt = t*2;   //150
const int ttt = t*3;  //225
const int tv = t*5;   //375
const int tvii = t*7; //525
/* ****************************************************
 *  I was going to attempt the figure out a better timing
 *  scheme.  Hasn't been implemented yet.
 */
//Whole note = 4 beats
//half note = 2 beats
//quarter note = 1 beat
//eighth note = 1/3 beat
//sixteenth note = 1/4 beat
//a doted not adds and aditional 1/2 length of note
//  so a doted quarter note = 1.5 beats
//Stacatto play note shorter
//Sheet music half note = 200 with 2/2 time signature
const int tq = 100;              //quarter note duration
const int t14 = round(tq*1/4);  // 1/16 note
const int t24 = round(tq*2/4);  // 1/8 note
const int t34 = round(tq*3/4);  // dotted 1/8 note
const int t2s = round(tq*3/2);  // Stacatto half note

//Pin Assignments
// Avoid Pins 0 & 1, since they are also used by the serial port
const int ledLeftPin = 14;     //Also known as A0
const int ledCenterPin = 17;   //Also known as A3
const int ledRightPin = 19;    //Also known as A5
const int leftBuzzer = 12;
const int centerBuzzer = 6;
const int rightBuzzer = 2;

int Sonic = 20000;

void setup(){
  left.begin(leftBuzzer);
  right.begin(rightBuzzer);
  center.begin(centerBuzzer);
  
  pinMode(ledLeftPin, OUTPUT);
  pinMode(ledCenterPin, OUTPUT);
  pinMode(ledRightPin, OUTPUT);
}

void loop(){
  mario0();
  mario1();
  mario2();
  mario1();
  mario2();
  mario3();
  mario4();
  mario3();
  mario5();
  mario3();
  mario4();
  mario3();
  mario5();
  mario6();
  mario7();
  mario6();
  mario0();
  mario1();
  mario2();
  mario1();
  mario2();
  mario8();
  mario9();
  mario8();
  marioa();
  mario8();
  mario9();
  mario8();
  marioa();
  mario6();
  mario7();
  mario6();
  mario0();
  mario8();
  mario9();
  mario8();
  marioa();

  //Infinite Loop
  while(1);
}

/* ***********************************************************
 *                         Functions
 * *********************************************************** */
void wait(Tone t){
  while (t.isPlaying()) { }  
}

void silence(int delayValue){
  left.play(Sonic,delayValue);
  wait(left); 
}
void soundThree(int note1, int note2, int note3, int tempo){
  digitalWrite(ledLeftPin, HIGH);
  left.play(note1, tempo); 
  right.play(note2, tempo); 
  center.play(note3, tempo);
  //delay(tempo);
  wait(center);
  left.stop();
  right.stop();
  digitalWrite(ledLeftPin, LOW);
}

void soundTwo(int note1, int note2, int tempo){
  digitalWrite(ledCenterPin, HIGH);
  //int bigdelay = tempo - 4;
  left.play(note1, tempo); 
  right.play(note2, tempo); 
  wait(right);
  //delay(bigdelay);
  digitalWrite(ledCenterPin, LOW);
}

void soundsOne(int note1, int tempo){
  digitalWrite(ledRightPin, HIGH);
  //int bigdelay = tempo + 1;
  left.play(note1, tempo); 
  //delay(bigdelay);
  wait(left);
  digitalWrite(ledRightPin, LOW);
}
  
void mario0(){
  soundThree(NOTE_FS3,NOTE_E4,NOTE_D3,t);
  silence(t);
  soundThree(NOTE_FS3,NOTE_E4,NOTE_D3,t);
  silence(ttt);
  soundThree(NOTE_FS3,NOTE_E4,NOTE_D3,t);
  silence(ttt);
  soundThree(NOTE_FS3,NOTE_C4,NOTE_D3,t);
  silence(t);
  soundThree(NOTE_FS3,NOTE_E4,NOTE_D3,t);
  silence(ttt);
  soundThree(NOTE_B3,NOTE_G4,NOTE_F4,t);
  silence(tvii);
  soundTwo(NOTE_G3,NOTE_G3,t);
  silence(tvii);
}

void mario1(){
  soundThree(NOTE_E3,NOTE_C4,NOTE_G3,t);
  silence(tv);
  soundThree(NOTE_C3,NOTE_G3,NOTE_E3,t);
  silence(tv);
  soundThree(NOTE_G2,NOTE_E3,NOTE_C3,t);
  silence(tv);
  soundThree(NOTE_C3,NOTE_A3,NOTE_F3,t);
  silence(ttt);
  soundThree(NOTE_D3,NOTE_B3,NOTE_G3,t);
  silence(ttt);
  soundThree(NOTE_CS3,NOTE_AS3,NOTE_FS3,t);
  silence(t);
  soundThree(NOTE_C3,NOTE_A3,NOTE_F3,t);
  silence(ttt);
}

void mario2(){
  soundThree(NOTE_C3,NOTE_G3,NOTE_E3,t);
  silence(tt);
  soundThree(NOTE_G3,NOTE_E4,NOTE_C4,t);
  silence(tt);
  soundThree(NOTE_B3,NOTE_G4,NOTE_E4,t);
  silence(tt);
  soundThree(NOTE_C4,NOTE_A4,NOTE_F4,t);
  silence(ttt);
  soundThree(NOTE_A3,NOTE_F4,NOTE_D4,t);
  silence(t);
  soundThree(NOTE_B3,NOTE_G4,NOTE_E4,t);
  silence(ttt);
  soundThree(NOTE_A3,NOTE_E4,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_E3,NOTE_C4,NOTE_A3,t);
  silence(t);
  soundThree(NOTE_F3,NOTE_D4,NOTE_B3,t);
  silence(t);
  soundThree(NOTE_D3,NOTE_B3,NOTE_G3,t);
  silence(tv);
}

void mario3(){
  soundsOne(NOTE_C3,t);
  silence(t);
  soundTwo(NOTE_E4,NOTE_G4,t);
  silence(t);
  soundThree(NOTE_DS4,NOTE_FS4,NOTE_G3,t);
  silence(t);
  soundTwo(NOTE_D4,NOTE_F4,t);
  silence(t);
  soundTwo(NOTE_B3,NOTE_DS4,t);
  silence(t);
  soundsOne(NOTE_C4,t);
  silence(t);
  soundTwo(NOTE_C4,NOTE_E4,t);
  silence(t);
  soundsOne(NOTE_F3,t);
  silence(t);
  soundTwo(NOTE_E3,NOTE_GS3,t);
  silence(t);
  soundTwo(NOTE_F3,NOTE_A3,t);
  silence(t);
  soundThree(NOTE_G3,NOTE_C4,NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_C4,t);
  silence(t);
  soundTwo(NOTE_C3,NOTE_A3,t);
  silence(t);
  soundThree(NOTE_E3,NOTE_C4,NOTE_F3,t);
  silence(t);
  soundTwo(NOTE_F3,NOTE_D4,t);
  silence(t);
}

void mario4(){
  soundsOne(NOTE_C3,t);
  silence(ttt);
  soundTwo(NOTE_E4,NOTE_G4,t);
  silence(t);
  soundThree(NOTE_DS4,NOTE_FS4,NOTE_E3,t);
  silence(t);
  soundTwo(NOTE_D4,NOTE_F4,t);
  silence(t);
  soundTwo(NOTE_B3,NOTE_DS4,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(t);
  soundThree(NOTE_C4,NOTE_E4,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_F4,NOTE_C5,NOTE_G5,t);
  silence(ttt);
  soundThree(NOTE_F4,NOTE_C5,NOTE_G5,t);
  silence(t);
  soundThree(NOTE_F4,NOTE_C5,NOTE_G5,t);
  silence(ttt);
  soundsOne(NOTE_G3,t);
  silence(ttt);
}

void mario5(){
  soundsOne(NOTE_C3,t);
  silence(ttt);
  soundThree(NOTE_GS3,NOTE_DS4,NOTE_GS3,t);
  silence(tv);
  soundThree(NOTE_F3,NOTE_D4,NOTE_B3,t);
  silence(tv);
  soundThree(NOTE_E3,NOTE_C4,NOTE_C4,t);
  silence(tv);
  soundsOne(NOTE_G3,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(ttt);
  soundsOne(NOTE_C3,t);
  silence(ttt);
}

void mario6(){
  soundThree(NOTE_GS3,NOTE_C4,NOTE_GS2,t);
  silence(t);
  soundTwo(NOTE_GS3,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_GS3,NOTE_C4,NOTE_DS3,t);
  silence(ttt);
  soundTwo(NOTE_GS3,NOTE_C4,t);
  silence(t);
  soundThree(NOTE_AS3,NOTE_D4,NOTE_GS3,t);
  silence(ttt);
  soundThree(NOTE_G3,NOTE_E4,NOTE_G3,t);
  silence(t);
  soundTwo(NOTE_E3,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_E3,NOTE_A3,NOTE_C3,t);
  silence(t);
  soundTwo(NOTE_C3,NOTE_G3,t);
  silence(ttt);
  soundsOne(NOTE_G2,t);
  silence(ttt);
}

void mario7(){
  soundThree(NOTE_GS3,NOTE_C4,NOTE_GS2,t);
  silence(t);
  soundTwo(NOTE_GS3,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_GS3,NOTE_C4,NOTE_DS3,t);
  silence(ttt);
  soundTwo(NOTE_GS3,NOTE_C4,t);
  silence(t);
  soundThree(NOTE_AS3,NOTE_D4,NOTE_GS3,t);
  silence(t);
  soundTwo(NOTE_G3,NOTE_E4,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(tv);
  soundsOne(NOTE_C3,t);
  silence(tv);
  soundsOne(NOTE_G2,t);
  silence(ttt);
}

void mario8(){
  soundThree(NOTE_C4,NOTE_E4,NOTE_C3,t);
  silence(t);
  soundTwo(NOTE_A3,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_E3,NOTE_G3,NOTE_FS3,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(ttt);
  soundThree(NOTE_E3,NOTE_GS3,NOTE_C4,t);
  silence(ttt);
  soundThree(NOTE_F3,NOTE_A3,NOTE_F3,t);
  silence(t);
  soundTwo(NOTE_C4,NOTE_F4,t);
  silence(t);
  soundsOne(NOTE_F3,t);
  silence(t);
  soundTwo(NOTE_C4,NOTE_F4,t);
  silence(t);
  soundThree(NOTE_F3,NOTE_A3,NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_F3,t);
  silence(ttt);
}

void mario9(){
  soundThree(NOTE_G3,NOTE_B3,NOTE_D3,t);
  silence(t);
  soundTwo(NOTE_F4,NOTE_A4,t);
  silence(tt);
  soundTwo(NOTE_F4,NOTE_A4,t);
  soundsOne(NOTE_F3,t);
  silence(t);
  soundThree(NOTE_F4,NOTE_A4,NOTE_G3,t);
  silence(t);
  soundTwo(NOTE_E4,NOTE_G4,t);
  silence(t);
  soundsOne(NOTE_B3,t);
  soundTwo(NOTE_D4,NOTE_F4,t);
  silence(tt);
  soundThree(NOTE_C4,NOTE_E4,NOTE_G3,t);
  silence(t);
  soundTwo(NOTE_A3,NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(t);
  soundTwo(NOTE_F3,NOTE_A3,t);
  silence(t);
  soundThree(NOTE_E3,NOTE_G3,NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(ttt);
}

void marioa(){
  soundThree(NOTE_G3,NOTE_B3,NOTE_G3,t);
  silence(t);
  soundTwo(NOTE_D4,NOTE_F4,t);
  silence(ttt);
  soundThree(NOTE_D4,NOTE_F4,NOTE_G3,t);
  silence(t);
  soundThree(NOTE_D4,NOTE_F4,NOTE_G3,t);
  silence(t);
  soundThree(NOTE_C4,NOTE_E4,NOTE_A3,t);
  silence(tt);
  soundThree(NOTE_B3,NOTE_D4,NOTE_B3,t);
  silence(tt);
  soundThree(NOTE_G3,NOTE_C4,NOTE_C4,t);
  silence(t);
  soundsOne(NOTE_E3,t);
  silence(t);
  soundsOne(NOTE_G3,t);
  silence(t);
  soundsOne(NOTE_E3,t);
  silence(t);
  soundTwo(NOTE_C3,NOTE_C3,t);
  silence(tvii);
}

