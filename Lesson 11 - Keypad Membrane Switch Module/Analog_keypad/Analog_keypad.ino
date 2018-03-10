/*Analog Keypad - using the Membrane Switch Module 
 *  By Ricardo Moreno
 *  02/13/208
 *
 * Using the Membrane Switch Module without a Library
 * and one analog pin
 * 
 * Inspired by:
 * HariFun #143 - How to read a 4x4 keypad using just one Arduino pin!
 * https://www.youtube.com/watch?v=G14tREsVqz0
 */
/* ******************* GLOBAL CONSTANTS ********************** */
const int analogPin = A0;                                     //Analog pin that we are connecting to

/* ******************* GLOBAL VARIABLES ********************** */
//Analog values for various resistor ladder values
int analogValues[] = {0,68,128,181, 
                    220,263,301,336,
                    362,391,418,443,
                    461,483,502,520};

//Keypad character values, Row0 through Row3
//char* keypadButton[] = {"1","2","3","A",
//                       "4","5","6","B",
//                       "7","8","9","C",
//                       "*","0","#","D"};
char keypadButton[] = "123A456B789C*0#D";
              
int analogValuesSize;   
              
/* *******************************************************
 *                         Setup
 ********************************************************* */
void setup(){
  // setup code:
  Serial.begin(9600);
  analogValuesSize = sizeof(analogValues)/sizeof(int);    //Get the array size 
}

/* *******************************************************
 *                      Void Loop
 ********************************************************* */
void loop(){
  // main code:
  int value = analogRead(analogPin);                     //get analog value

  if (value<1000){ analogKeyPress(value);}               //if the value is something other than 1023
                                                         //  run analogKeyPress subroutine
}

/* *******************************************************
 *                       Functions
 ********************************************************* */

int debounce(int last){
  /* function debounce - button debouncing routine. Double-checks the button press to value
   * Parameter:
   *   last - what the initial value was
   */
  //Local Variable
  delay(10);                                             //Small delay
  int current = analogRead(analogPin);                   //get latest analog value

  if(abs(current - last) > 5){                           //if current >> last then get a new value
    delay(5);                        //5 milliseconds
    current = analogRead(analogPin);
  }
  return current;                                        //Return analog value
}

void analogKeyPress(int value){
  /* subroutine analogKeyPress - Sends the keypressed to the serial monitor 
   * Parameter:
   *   value - passed analog read value
   */
  value = debounce(value);                              //Call Debounce routine and get final value
  for (int i = 0; i < analogValuesSize; i++){           //Search through analogValues to get keypad pressed
    if (abs(value - analogValues[i]) < 5){
      Serial.println(keypadButton[i]);                  //Send keypad character to Serial Monitor
      //Serial.println(value);
      
      while(analogRead(analogPin) < 1000){delay(100);}  //Wait until keypad button is released
    }
  }
}

