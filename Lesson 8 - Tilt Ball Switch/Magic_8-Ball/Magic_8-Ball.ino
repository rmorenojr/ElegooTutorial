/* For the Lession 7 - Tilt Ball Switch
 * Magic-8 ball using an LCD display
 * by Ricardo Moreno
 * https://github.com/rmorenojr/ElegooTutorial
 *
 * Inspired by Arduino Video Tutorial-07 Crystal Ball Magic Ball - by Arduino
 * https://www.youtube.com/watch?v=kmIy1Y0Jwo8
 *
 * Arduino LiquidCrystal web page
 * https://www.arduino.cc/en/Reference/LiquidCrystal
 * https://github.com/codebendercc/arduino-library-files/tree/master/libraries/LiquidCrystal
 *
 */
#include <LiquidCrystal.h>

//Initialize library with LCD screen
//LiquidCrystal(rs, enable, d4, d5, d6, d7) 
//  or
//LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);     //instantiates the LiquiCrystal Object class to variable lcd

//Global Constants
const int tiltSensorPin = 6;
//Global Variables
bool currentSwitchState = LOW;                 //bool is the standard, and preferred type for boolean
bool prevSwitchState = LOW;
int reply;

void setup(){
   lcd.begin(16, 2);                        //16 characters and two lines
   pinMode(tiltSensorPin, INPUT_PULLUP);    //sets the pinmode for the tilt sensor
   lcd.print("Ask the");                    //prints the line of text
   lcd.setCursor(0,1);                      //moves the cursor to the next line
   lcd.print("Magic 8-Ball!");              //not sure if hyphen will work
}

void loop(){
  currentSwitchState = debounce(prevSwitchState);  //get the tilt sensor value HIGH or LOW

  if (currentSwitchState != prevSwitchState) {     //looking for a change in the tilt sensor
    if (currentSwitchState == LOW) {              //tilt sensor has made a connection
      lcd.clear();                               //clear the screen
      reply = random(8);                         //random select a number from 0-7
      lcd.setCursor(0, 0);                       //move cursor
      lcd.print("8-ball says:");                 //print the line of text
      lcd.setCursor(0, 1);                       //move the cursor
        
      switch(reply){                             //switch statement jumps to case with a reply value (0-7)
        case 0:
          lcd.print("Yes");
          break;
        case 1:
          lcd.print("Most likely");
          break;
        case 2:
          lcd.print("Certainly");
          break;
        case 3:
          lcd.print("Outlook good");
          break;   
        case 4:
          lcd.print("Unsure");
          break;   
        case 5:
          lcd.print("Ask again");
          break;   
        case 6:
          lcd.print("Doubtful");
          break;   
        case 7:
          lcd.print("No");
          break;   
      }
    }
    else {                                         //Detected that the switch is HIGH or tilted down
        lcd.clear();                               //clear the screen
        lcd.setCursor(0, 0);                       //move cursor
        lcd.print("8-ball says:");                 //print the line of text
        lcd.setCursor(0, 1);                       //move the cursor
    }
     
  }
  //Save the current state into previous state
  prevSwitchState = currentSwitchState;
}

/* ***********************************************************
 *                         Functions
 * *********************************************************** */
 
//Debouncing function
bool debounce(boolean last){
  //Local Variable
  bool current = digitalRead(tiltSensorPin);

  if(last != current){
    delay(100);                                //100 milliseconds
    current = digitalRead(tiltSensorPin);
  }
  return current;
}

