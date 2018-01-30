/* Arduino + Star Wars Imperial March (Buzzer/Piezo)
 * Modified by Ricardo Moreno
 * https://github.com/rmorenojr/ElegooTutorial
 * 01/21/2018 
 * 
 * Original by Profe-Electro
 * https://www.youtube.com/watch?v=83xHpj3PstI
 */
#include <pitches.h>

//Global Constants
const int melodyBuzzerPin = 6;             // Digital Pin 8
const int leftLedPin = 19;                 // Analog Pin A5
const int rightLedPin = 17;                // Analog Pin A3

/* I couldn't figure out the timing of this score
 *  perhaps I'll revise it in the future
 *  Imperial March 
 *  Ala Marcia  1/4 note = 112 on sheet music
 *  https://www.youtube.com/watch?v=4pwcsn0TU0Q
 */
// Timing
const int t4 = 125;                  // quarter note duration in ms
const int td4 = t4*1.5;              // dotted quarter note
const int tL4 = t4*1.3;              // Legato quarter note
const int t2 = t4*2;                 // half note
const int td2 = t4*3;                // dotted half note
const int tL2 = t2*1.3;              // Legato half note
const int wt = t4*4;                 // whole note
const int wtL = wt*1.3;              // whole note
const int t16 = round(t4*1/4);       // 1/16 note 
const int t8 = round(t4*1/2);        // 1/8 note
const int tL8 = round(t8*1.3);       // Legato 1/8 note
const int td8 = round(t8*1.5);       // dotted 1/8 note
const int ts8 = round(t8*.8);        // Stacatto 1/8 note

boolean FlipFlop = true;             // LED state 

void setup(){
  //Setup pin modes
  pinMode(melodyBuzzerPin, OUTPUT); 
  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);
}

void loop(){
  //Play first section
  firstSection();

  //Play second section
  secondSection();

  //Variant 1
  beep(NOTE_F4, t2);  
  beep(NOTE_GS4, wt);  
  beep(NOTE_F4, tL2);  
  beep(NOTE_A4, t4);
  beep(NOTE_C5, wt);
  beep(NOTE_A4, td2);  
  beep(NOTE_C5, t4);
  beep(NOTE_E5, wtL);

  delay(wt);

  //Repeat second section
  secondSection();

  //Variant 2
  beep(NOTE_F4, t2);  
  beep(NOTE_GS4, wt);  
  beep(NOTE_F4, td2);  
  beep(NOTE_C5, t4);
  beep(NOTE_A4, wt);  
  beep(NOTE_F4, td2);  
  beep(NOTE_C5, t4);
  beep(NOTE_A4, wtL);  

  delay(wtL);
}

/* ***********************************************************
 *                         Functions
 * *********************************************************** */

void beep(int note, int duration){
  //Play tone on melodyBuzzerPin
  tone(melodyBuzzerPin, note, duration);

  if(FlipFlop){
    digitalWrite(leftLedPin, HIGH);
  }
  else {
    digitalWrite(rightLedPin, HIGH);
  }
  delay(duration);
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);
  FlipFlop = !FlipFlop;

  //Stop tone on melodyBuzzerPin
  noTone(melodyBuzzerPin);

  delay(ts8);
}

void firstSection(){
  beep(NOTE_A4, wt);
  beep(NOTE_A4, wt);    
  beep(NOTE_A4, wt);
  beep(NOTE_F4, tL2);
  beep(NOTE_C5, tL4);  
  beep(NOTE_A4, wt);
  beep(NOTE_F4, tL2);
  beep(NOTE_C5, tL4);
  beep(NOTE_A4, wtL);

  delay(wt);

  beep(NOTE_E5, wt);
  beep(NOTE_E5, wt);
  beep(NOTE_E5, wt);  
  beep(NOTE_F5, tL2);
  beep(NOTE_C5, tL4);
  beep(NOTE_GS4, wt);
  beep(NOTE_F4, tL2);
  beep(NOTE_C5, tL4);
  beep(NOTE_A4, wtL);

  delay(wt);
}

void secondSection(){
  beep(NOTE_A5, wt);
  beep(NOTE_A4, tL2);
  beep(NOTE_A4, tL4);
  beep(NOTE_A5, wt);
  beep(NOTE_GS5, tL2);
  beep(NOTE_G5, td4);
  beep(NOTE_FS5, t4);
  beep(NOTE_F5, t4);    
  beep(NOTE_FS5, t2);

  delay(tL2);

  beep(NOTE_AS4, t2);
  beep(NOTE_DS5, wt);
  beep(NOTE_D5, tL2);  
  beep(NOTE_CS5, td4);  
  beep(NOTE_C5, t4);  
  beep(NOTE_B4, t4);  
  beep(NOTE_C5, t2);  

  delay(tL2);
} 

