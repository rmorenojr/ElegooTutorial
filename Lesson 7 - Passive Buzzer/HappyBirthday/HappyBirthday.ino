/*  Happy Birthday Melody On Arduino UNO With 3-way Polyphony
 *  Modified by Ricardo Moreno Jr.
 *  https://github.com/rmorenojr/ElegooTutorial
 *  01/21/2018 
 *   
 *  Original for the Arduion Nano - by Liss
 *  https://www.hackster.io/liss/happy-birthday-melody-on-arduino-nano-with-3-way-polyphony-c80c31
 *  
 *
 *  
 *  For use with newer Tone-Master by bhagman
 *  https://github.com/bhagman/Tone
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
 */
#include <Tone.h>
//Each Tone calss object uses an internal timer
Tone solo;                          // Plays the standard Happy Birthday music
Tone bass;                          // Plays the low pitch past switching music
Tone rythm;                         // Plays the high pitches fast switching music
//Note: with 3 timers used with above Tone class objects - 
//the delay() function will no longer work.  

//Global Constants
// Timing
const int t4 = 600;                  // quarter note duration in ms
const int t2 = t4*2;                 // half note
const int td2 = t4*3;                // dotted half note
const int wt = t4*4;                 // whole note
const int t16 = round(t4*1/4);       // 1/16 note
const int t8 = round(t4*1/2);        // 1/8 note
const int td8 = round(t4*3/4);       // dotted 1/8 note
const int ts8 = round(t8*.8);        // Stacatto 1/8 note
 
//Pin Assignments
// Avoid Pins 0 & 1, since they are also used by the serial port
const int bassLedPin = 14;          // bass led signal pin (aka A0)
const int rythmLedPin = 17;         // rythm led signal pin (aka A3)
const int soloLedPin = 19;          // solo led signal pin (aka A5)
const int bassBuzzerPin = 12;       // bass buzzer signal pin
const int rythmBuzzerPin = 6;       // rythm buzzer signal pin
const int soloBuzzerPin = 2;        // solo buzzer signal pin

boolean bassLedState = LOW;
boolean rythmLedState = LOW;
boolean soloLedState = LOW;

int Sonic = 20000;                  //The high frequency for the delay

void setup(void){
  /* *******     Ground Pins Setup    ********
   * If your circuit constraints require that you 
   * accomidate ground pins elsewhere, changing the
   * pin to OUTPUT will create the LOW to complete
   * the circuit.
   */ 
  //pinMode(15, OUTPUT);            // led ground pin (aka A1)
  //pinMode(16, OUTPUT);            // led ground pin (aka A2)
  //pinMode(18, OUTPUT);            // led ground pin (aka A4)
  //pinMode(2, OUTPUT);             // solo buzzer ground pin
  //pinMode(9, OUTPUT);             // rythm buzzer ground pin 

  //LED pins setup
  pinMode(bassLedPin, OUTPUT);      // bass led signal pin
  pinMode(rythmLedPin, OUTPUT);     // rythm led signal pin
  pinMode(soloLedPin, OUTPUT);      // solo led signal pin

  //Buzzer pins setup
  solo.begin(soloBuzzerPin);       // solo buzzer signal pin
  bass.begin(bassBuzzerPin);       // bass buzzer signal pin
  rythm.begin(rythmBuzzerPin);     // rythm buzzer signal pin
}

void loop(void){
  //Happy Birthday Music Score
          solo.play(NOTE_D4, td8); switchSoloLed();
          wait(solo);
          solo.play(NOTE_D4, t16); switchSoloLed();
          wait(solo);
  bass.play(NOTE_G3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_E4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);
  
  bass.play(NOTE_B3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_D4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);
  bass.play(NOTE_D4, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_G4, t4); switchSoloLed();
          wait(rythm); 
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);
  
  bass.play(NOTE_D4, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          solo.play(NOTE_FS4, t2); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();
          wait(rythm);
  bass.play(NOTE_FS4, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();
          wait(rythm);
  bass.play(NOTE_A4, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          solo.play(NOTE_D4, td8); switchSoloLed();
          wait(rythm);        
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();    
          solo.play(NOTE_D4, t16); switchSoloLed();
          wait(rythm);
  
  bass.play(NOTE_D4, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          solo.play(NOTE_E4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();
          wait(rythm);        
  bass.play(NOTE_FS4, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          solo.play(NOTE_D4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();
          wait(rythm);         
  bass.play(NOTE_A4, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          solo.play(NOTE_A4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();
          wait(rythm);  
  
  bass.play(NOTE_G3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_G4, t2); switchSoloLed();
          wait(rythm);        
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);
  bass.play(NOTE_B3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);        
  bass.play(NOTE_D4, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_D4, td8); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();       
          solo.play(NOTE_D4, t16); switchSoloLed();
          wait(rythm);
  
  bass.play(NOTE_G3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_D5, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);        
  bass.play(NOTE_B3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_B4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);          
  bass.play(NOTE_D4, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_G4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);       
  
  bass.play(NOTE_C4, t4); switchBassLed();
    rythm.play(NOTE_C5, t8); switchRythmLed();
          solo.play(NOTE_FS4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_E5, t16); switchRythmLed();  
          wait(rythm);
    rythm.play(NOTE_G5, t16); switchRythmLed();   
          wait(rythm);       
  bass.play(NOTE_E4, t4);  switchBassLed();
    rythm.play(NOTE_C5, t8); switchRythmLed();
          solo.play(NOTE_E4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_E5, t16); switchRythmLed();   
          wait(rythm);
    rythm.play(NOTE_G5, t16); switchRythmLed();   
          wait(rythm);          
  bass.play(NOTE_G4, t4); switchBassLed();
    rythm.play(NOTE_C5, t8); switchRythmLed();
          solo.play(NOTE_C5, td8); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_E5, t16); switchRythmLed();
          wait(rythm); 
    rythm.play(NOTE_G5, t16); switchRythmLed();     
          solo.play(NOTE_C5, t16); switchSoloLed();
          wait(rythm);
  
  bass.play(NOTE_G3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_B4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);         
  bass.play(NOTE_D3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_G4, t4); switchSoloLed();
          wait(rythm);
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm); 
  bass.play(NOTE_FS3, t4); switchBassLed();
    rythm.play(NOTE_D5, t8); switchRythmLed();
          solo.play(NOTE_A4, t4); switchSoloLed();
          wait(rythm);
          wait(rythm);
    rythm.play(NOTE_FS5, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_A5, t16); switchRythmLed();
          wait(rythm);          
  
  bass.play(NOTE_G3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed();
          solo.play(NOTE_G4, t2); switchSoloLed();
          wait(rythm);        
    rythm.play(NOTE_B4, t16); switchRythmLed();
          wait(rythm);
    rythm.play(NOTE_D5, t16); switchRythmLed();
          wait(rythm);
  bass.play(NOTE_B3, t4); switchBassLed();
    rythm.play(NOTE_G4, t8); switchRythmLed(); 
          wait(rythm);
          //Turn off rythm LED
          rythmLedState = HIGH; switchRythmLed();
    //rythm.play(NOTE_B4, t16); switchRythmLed();
          //wait(rythm);
    //rythm.play(NOTE_D5, t16); switchRythmLed();
          //wait(rythm);
          wait(bass);
          //Turn off bass LED
          bassLedState = HIGH; switchBassLed();
          wait(solo);
          //Turn off solo LEDs
          soloLedState = HIGH; switchSoloLed();
          
          //small pause before continuing
          //can't use delay with three timers in use
          solo.play(Sonic,ts8);
          wait(solo);      
}

/* ***********************************************************
 *                         Functions
 * *********************************************************** */
 
void wait(Tone t){
  while (t.isPlaying()) { }  
}

void switchBassLed(){
  bassLedState = !bassLedState;
  digitalWrite(bassLedPin, bassLedState);
}

void switchRythmLed(){
  rythmLedState = !rythmLedState;
  digitalWrite(rythmLedPin, rythmLedState);
}

void switchSoloLed(){
  soloLedState = !soloLedState;
  digitalWrite(soloLedPin, soloLedState);
}

