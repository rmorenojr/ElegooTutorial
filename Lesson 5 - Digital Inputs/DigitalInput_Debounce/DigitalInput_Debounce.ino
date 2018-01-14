/* The Most Complete Starter Kit by Elegoo
 *  For the Arduino UNO R3
 *  LESSON 5 - Digital Input(s)
 *  Single button with debounce function
 *  
 *  Original by - Applied Electronics, lynda.com, and Elegoo.com
 *  Modified by - Ricardo Moreno
 *  Date 1/9/2018
 *
 *  Originally, the Lesson 5 sketch used two push button switches
 *  to operate the LED.  This sketch allows for a single push button
 *  switch.
 *
 *  Serial Monitor added for diagnostic purposes.
 *
 *  Applied Electronics 
 *  https://www.youtube.com/watch?v=QslLAPNSEFc
 */
//usefull video to watch from educ8s.tv
//https://www.youtube.com/watch?v=jYOYgU2vlSE

// Global Variables
const int ledPin = 5;
const int buttonPin = 2;             
boolean lastButton = HIGH;           //HIGH is the not pressed state
boolean currentButton = HIGH;        //HIGH is the not pressed state
boolean ledOn = false;
int counter = 0;

// Sketch Setup routine - run once
void setup(){
  Serial.begin(9600);                //starts the serial monitor and sets the baud rate
  pinMode(ledPin, OUTPUT);           //sets the digital pin to output
  pinMode(buttonPin, INPUT_PULLUP);  //define pinMode and use Pull-up resistor
  serialOut(ledOn,counter);          //write the initial state of the LED
}

// main loop - runs repeatedly
void loop(){
  //Get button value or state
  currentButton = debounce(lastButton);
  
  //Recall that whenever you release the button, the state goes HIGH
  //When you press the button, you are forcing the state LOW
  if(lastButton == LOW && currentButton == HIGH){
    //Button press detected
    counter += 1;                    //increment the counter
    ledOn = !ledOn;                  //shorthand way to switch to the opposite setting
    digitalWrite(ledPin, ledOn);     //Turn ON or OFF the LED
    serialOut(ledOn,counter);        //write the state of the LED and number of time the button has been pushed
  }
  lastButton = currentButton;
}

//Debouncing function
boolean debounce(boolean last){
  //Local Variable
  boolean current = digitalRead(buttonPin);

  if(last != current){
    delay(5);                        //5 milliseconds
    current = digitalRead(buttonPin);
  }
  return current;
}

//Serial Output function
void serialOut(boolean ledState, int i){ 
  Serial.print("LED is ");
  if (ledState) Serial.print("ON - button pressed ");
  if (!ledState) Serial.print("OFF - button pressed ");
  Serial.print(i);
  Serial.println(" times");
}
