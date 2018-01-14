/* The Most Complete Starter Kit by Elegoo
 *  For the Arduino UNO R3
 *  LESSON 5 - Digital Input(s)
 *  Using Interrupt, Low Power, Deep Sleep
 *  
 *  Original by - Kevin Darrah
 *  Modified by - Ricardo Moreno
 *  Date 1/10/2018
 *
 *  Originally, the Lesson 5 sketch used two push button switches
 *  to operate the LED.  This sketch uses a single push button
 *  switch activating an interrupt, waking up the Arduino. It runs the 
 *  code inside the void loop and automatically goes into a deep sleep.  
 *  It also has a watchdog timer to to automatically wake the circuit 
 *  every 8 seconds.
 *  
 *  Kevin Darrah does a great job flipping bits without the need for an
 *  external library. He does an awesome job explaining this deep sleep setup.
 *
 *  Serial Monitor added for diagnostic purposes.
 *
 *  Kevin Darrah - Low Power Arduino! Deep Sleep Tutorial
 *  https://www.youtube.com/watch?v=urLSDi7SD8M&t
 */
//Page of interest
//https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

// Global Variables
const int ledPin = 5;
const int buttonPin = 2;             //Arduino UNO requires pins 2 or 3
volatile int counter = 0;

// Sketch Setup routine - run once
void setup(){
  Serial.begin(9600);                //starts the serial monitor and sets the baud rate
  pinMode(buttonPin, INPUT_PULLUP);  //define pinMode and use Pull-up resistor
  
  //Save Power by writing all Digital IO pins to LOW
  //  Of course be carefull not to include pins you are using
  //  not skipping LED pin is OK 
  for (int i = 0; i < 20; i++) {
    if(i != buttonPin){              //we're using pin 2 for the button
      pinMode(i, OUTPUT);
      digitalWrite(i, LOW);
    }
  }
  //pinMode(ledPin, OUTPUT);         //sets the digital pin to output - handled by above for loop

  /* attachInterrupt syntax
   *
   * attachInterrupt(interrupt, ISR, mode)
   *
   * interrupt  can be either 0 or 1 for interrupts on pins 2 or 3.
   *            recommend using the following code
   *            digitalPinToInterrupt(pin) 
   * 
   *       ISR  Interrupt Service Routine - Name of a function
   *            you want to execute after interrupt above
   *
   *      mode� When the interrupt should be triggered. Options:
   *             LOW        a low level trigger
   *             CHANGE     a change in level trigger
   *             RISING     a rising edge of a level trigger
   *             FALLING    a falling edge of a level trigger
   *
   */  
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, RISING); 
  serialOut(false, counter);          //write the initial state of the LED

  /*SETUP WATCHDOG TIMER
   *  This is set for about 8 seconds
   *  See manufacturer's data sheet for other options
   *  WDTCSR = 
   *  bits  7  |   6  |  5   |   4  |  3  |   2  |   1  |   0
   *      WDIF | WDIE | WDP3 | WDCE | WDE | WDP2 | WDP1 | WDP0
   *
   *  To enable and set the watchdog timer we must
   *  set WDCE and WDE bits but 
   *  Also clears/resets prescaler bits WDP3,WDP2,WDP1,WDP0
   *  See Watchdog Timer Control Register for more info
   *  24 = 00011000
   */
  WDTCSR = (24);                     
  /*  The above line must be followed by
   *  Setting the prescalers bits WDP3,WDP2,WDP1,WDP0.
   *  This gives us the 8 seconds based on table in data sheet. 
   *  We must also clear WDE and WDCE bits
   *  33 = 00100001
   */
  WDTCSR = (33);
  //  Now enable interrupt mode with new settings - set WDIE bit                     
  WDTCSR |= (1 << 6);                //uses compound bitwise OR operator shift register trick

  /*Disable Analog to Digital Converter (ADC)
   *  ADCSRA - ADC Control and Status Register A
   *  Set the ADEN bit to 0 to turn off ADC
   *  don't forget to flip back after waking up if using ADC
   *  in your application ADCSRA |= (1 << 7);
   */
  ADCSRA &= ~(1 << 7);               //uses compound bitwise AND operator and inverted shift register trick 
  
  /*ENABLE SLEEP MODE -
   *  Sleep Mode Control Register
   *  SMCR = 
   *  bits  7 | 6 | 5 | 4 |  3  |  2  |  1  |  0
   *        - | - | - | - | SM2 | SM1 | SM0 | SE
   *  bits 7-4 are unused
   *  SE - Sleep Enable bit
   *  
   *  Sleep Mode Table 
   *  SM2 | SM1 | SM0 | Sleep Mode
   *   0     0     0    Idle
   *   0     0     1    ADC noise reduction
   *   0     1     0    Power-down
   *   0     1     1    Power-save
   *   1     1     0    Standby +
   *   1     1     1    External Standby +
   *  + only recommended with external crystals or resonators
   *  See manufacturer's data sheet for other options
   *
   *  Using a technique to shift register bits 
   *  this enables the sleep mode
   *  be sure to have an interrupt enabled or the 
   *  watchdog timer to wake it up
   */
  //SET the sleep mode bit(s)
  SMCR |= (1 << 2);                  //power down mode
  SMCR |= 1;                         //enable sleep mode
}

// main loop - runs repeatedly
void loop(){
  Serial.println("Void loop starts");
  digitalWrite(ledPin, HIGH);
  serialOut(true, counter);
  /* Put all you running code here
   * Once it's complete it will go
   * back to sleep.
   */ 
  delay(1000);                      //delay not required
  digitalWrite(ledPin, LOW);
  serialOut(false, counter);

  goToSleep();
  Serial.println("Void loop ends");
}

void buttonInterrupt() {
  counter++;                        //increment the counter
  Serial.println("Button is pressed");
  //This returns to the goToSleep or void loop
}

//Serial Output function
void serialOut(boolean ledState, int i){ 
  Serial.print("LED is ");
  if (ledState) Serial.print("ON - button pressed ");
  if (!ledState) Serial.print("OFF - button pressed ");
  Serial.print(i);
  Serial.println(" times");
}

void goToSleep() {
   Serial.println("going to sleep");
   delay(60);                        //small delay is necessary otherwise it goes to sleep before serial.println is done
   /*Disable the Brownout Detect circuit while sleeping
   *  
   * this must be called right before the __asm__ sleep instruction
   * MCUCR - MCU Control Register
   *  bits  7 |   6  |   5   |  4  | 3 | 2 |   1   |   0
   *        - | BODS | BODSE | PUD | - | - | IVSEL | IVCE
   *
   * Set Both BODS and BODSE at the same time
   * 3 = 11
   */  
  MCUCR |= (3 << 5);                 
  //then set the BODS bit and clear the BODSE bit within 4 clock cycles
  //The trick below clears BODSE and sets BODS to 1 
  MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); 
  __asm__  __volatile__("sleep");    //in line assembler to go to sleep

  Serial.println("waking up");
}

// watchdog interrupt
ISR(WDT_vect){
  Serial.println("Watch dog is on duty");
  //DON'T FORGET THIS!  Needed for the watch dog timer.
  //  This is called after a watch dog timer timeout - 
  //  this is the interrupt function called after waking up
}
