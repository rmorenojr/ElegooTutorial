/* Servo Range Calibrator Sketch
 * by Ricardo Moreno Jr.
 * 02/03/2018
 * 
 * Arduino Servo Library
 * https://www.arduino.cc/en/Reference/Servo
 * https://github.com/arduino-libraries/Servo
 * Arduino Pin Change Inpterrupt
 * http://playground.arduino.cc/Main/PinChangeInterrupt
 * 
 *  Servo - Class for manipulating servo motors connected to Arduino pins.
 *  methods:
      attach(pin)             - Attaches a servo motor to an i/o pin.
      attach(pin, min, max)   - Attaches to a pin setting min and max values in microseconds
                                default min is 544, max is 2400 
      write()                 - Sets the servo angle in degrees.  (invalid angle that is valid
                                as pulse in microseconds is treated as microseconds)
      writeMicroseconds()     - Sets the servo pulse width in microseconds 
      read()                  - Gets the last written servo pulse width as an angle between 0 and 180. 
      readMicroseconds()      - Gets the last written servo pulse width in microseconds. 
                                (was read_us() in first release)
      attached()              - Returns true if there is a servo attached. 
      detach()                - Stops an attached servos from pulsing its i/o pin.
 *
 * Use the push button the the rotary encoder to start the calibration
 * Afterwards used the knog to turn the servo.
 *  
 * attachInterrupt(digitalPinToInterrupt(pin), InterruptServiceRoutines, mode) 
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * Arduino UNO - pins 2, 3 for interrupts 0, 1
 * Note:
 *      Inside the attached function, delay() won't work and the value returned by millis() 
 *      will not increment. Serial data received while in the function may be lost. You should 
 *      declare as volatile any variables that you modify within the attached function. See 
 *      the section on ISRs below for more information.
 * Note about Rotary Encoder - it is difficult to reduce the contact bouncing without some 
 * discrete components.  Circuit uses an inline resistor and capacitor.  Also see  
 * Kevin Darrah
 * https://www.youtube.com/watch?v=HQuLZHsGZdI
 */
/* ****************** INCLUDE LIBRARIES ********************** */
#include <Servo.h>
#include <U8g2lib.h>

Servo myServo;                  //Instantiate a Servo object
// twelve servo objects can be created on most boards

/* ******************* GLOBAL CONSTANTS ********************** */
//OLED Pins
const int oledClkpin = 13;
const int oledMosipin= 12;
const int oledRespin = 11;
const int oledDCpin  = 10;
const int oledCSpin  = 9; 
//Instantiate U8G2 object - Plus Pins
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ oledClkpin, /* data=*/ oledMosipin, /* cs=*/ oledCSpin, /* dc=*/ oledDCpin, /* reset=*/ oledRespin);

//Using the KY-040 Rotary Encoder Module
const int ePin_A = A1;                             //Encoder clock pin or Encoder pin A
const int ePin_B = A0;                             //Encoder DT signal pin or Encoder pin B
const int ePin_Button = 3;                         //Encoder SW pin Normally Open push button - Also Interrupt 1
//Servo SG90
const int myServoPin = 2;                          //Servo pin
//RGB LED
const int bLEDPin = 5;
const int gLEDPin = 6;
const int rLEDPin = 7;

/* ******************* GLOBAL VARIABLES ********************** */
//servo ranges in microseconds
int imin = 625;                                    // servo's absolute iminmum position in microseconds - through testing
int imax = 2625;                                   // servo's absolute imaxmum position in microseconds - through testing
int minPos = imin;                                 // My Initial value is 735 - determined through trial and error
int maxPos = imax;                                 // My initial value is 2349 - determined through trial and error
volatile bool ebutton = false;                     // Store adjustment mode state - Used by interrupt
volatile long eCounter = 0;                        // Stores rotary counts - Used by interrupt
bool bRotateLt = true;                             // Stores the servo rotation direction state 
int maxBright = 220;                               // Adjust LED brightness


/* ******************** SETUP FUNCTIONS ********************** */
void pciSetup(byte pin){
  //Setup function to setup Pin change interrupts
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable: pin PCMSK1 |= bit (PCINT8)
    PCIFR  |= bit (digitalPinToPCICRbit(pin));     // clear any outstanding interrupt: (PCIF1)
    PCICR  |= bit (digitalPinToPCICRbit(pin));     // enable interrupt for the group: (PCIE1)
}

/* *********************** VOID SETUP ************************ */
void setup(){
  //if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  myServo.attach(myServoPin, minPos, maxPos);      // Sets up Servo class object - datasheet values are not correct
                                                   // (pin#, pulse min microseconds, pulse max microseconds)
                                                   // (pin#, 544, 2400) - default values in library
  //Setting up section A0-A5
  for (int i=A0; i<=A5; i++) {
     pinMode(i, INPUT_PULLUP);                     // All pins are inputs with pull-up resistors
  }
  //pinMode(ePin_A, INPUT_PULLUP);                 // Encoder Clk pin A with pull up resistors
  //pinMode(ePin_B, INPUT_PULLUP);                 // Encoder DT signal pin B with pull up resistors
  pinMode(ePin_Button, INPUT_PULLUP);              // Encoder button pin with pull up resistors
  pinMode(bLEDPin, OUTPUT);                        // RGB LED
  pinMode(gLEDPin, OUTPUT); 
  pinMode(rLEDPin, OUTPUT); 

  //Attach to interrupt 1 on pin 3
  attachInterrupt(digitalPinToInterrupt(ePin_Button), eButton_isr, CHANGE);
  //Use Pin Change interrupt for A0 & A1
  pciSetup(ePin_A);                                // Encoder Clk pin A
  pciSetup(ePin_B);                                // Encoder DT signal pin B
  
  Serial.begin(115200);                            // Enable the serial monitor
  setColor(0,maxBright,0);                         // set the RGB LED to green

  //OLED Diplay
  /* U8g2 Project: SSD1306 OLED SPI Board */
  pinMode(oledDCpin, OUTPUT);
  pinMode(oledDCpin, OUTPUT);
  digitalWrite(oledDCpin, 0);
  digitalWrite(oledDCpin, 0);    
  u8g2.begin();   

  //Initial Serial Monitor Startup help message
  Serial.println("This routine helps you fine tune");
  Serial.println("your servo's min and max values");
  Serial.println("When the servo reaches either ");
  Serial.println("0 or 180 degrees, press the Encoder");
  Serial.println("button to fine tune the value");
  Serial.println("");  
}

/* *********************** VOID LOOP ************************* */
void loop() {
  //Check to see of Encoder button is pushed - test can be performed more that once
  if (ebutton==true){                                         // Encoder button has been pressed
    ebutton=false;
    
    //Adjustment mode routine
    Serial.println("Adjustment mode Started");

    //Go into edit mode
    int pos = myServo.readMicroseconds();                     // Read current postion in microseconds
    int midPos = round((maxPos-minPos)/2);
    if (pos <= midPos){                                       // current postion less that 90 degrees or half range   
      Serial.println("Adjust until 0 degrees");               // if you are closer to zero, assume adjusting min
    } else {                                                  // current position greater than 90 degrees or half range
      Serial.println("Adjust until 180 degrees");             // if you are closer to 180, assume adjusting max
    }
    Serial.print("Current postion in Microseconds = ");
    Serial.println(pos);

    ebutton=false;                                            // Just to make sure

    setColor(maxBright,maxBright/2,0);                        // RGB LED to Yellow
    //Loop until ebutton
    while (!ebutton){                                         // Wait intil done adjusting (button press) 
      doEncoder();
    }
    
    delay(1000);
    eCounter=0;
    ebutton=false;
    Serial.print("New min = "); Serial.print(minPos); Serial.print("  New max = "); Serial.println(maxPos);
    Serial.println("Make these changes to the code");
    Serial.println("");

  } else {

    serverRotate(bRotateLt);
    bRotateLt = !bRotateLt;                                  // Switch direction
    Serial.println("Press button to adjust");
  }

  setColor(0,maxBright,0);                                   // RGB LED to Green
  delay(3000);                                               // Wait 3 seconds for user input
}

/* ***********************************************************
 *                         Functions
 * *********************************************************** */
void draw(int cPos, int indicator=1){
  /*draw - refresh the OLED screen
   * Parameters:
   * cPos - current position in microseconds
   * [optional] indicator - move the indicator disc above
   *   0 - min 
   *   1 - cpos <default>
   *   2 - max
   */
  //Error checking
  if ((indicator > 2)||(indicator < 0)) indicator=1; 
  int indTable[] = {20,64,106};
  u8g2.firstPage();
  do {
    // draw(minPos, Pos, maxPos);
    // select font 
    u8g2.setFont(u8g2_font_9x15B_tf);

    u8g2.drawStr(2,15,"Servo Adjuster");
    //draw two lines
    u8g2.drawLine(2,20,124,20);                             //x0,y0,x1,y1
    u8g2.drawHLine(2,22,123);                               //x,y,w
    //Move Indicator dot into postion 
    u8g2.drawDisc(indTable[indicator], 28, 3, U8G2_DRAW_ALL);
    
    u8g2.drawStr(5,45,"Min");
    u8g2.drawStr(45,45,"CPOS");
    u8g2.drawStr(95,45,"Max");

    u8g2.setCursor(2,60);
    u8g2.print(minPos);

    u8g2.setCursor(45,60);
    u8g2.print(cPos);

    u8g2.setCursor(90,60);
    u8g2.print(maxPos);
  } while ( u8g2.nextPage() ); 
}

void setColor(int redValue, int greenValue, int blueValue){
  /*setcolor - RGB LED color - from Lesson 4
   *
   *Parameters:
   *  redvalue - 0-255
   *  greenValue - 0-255
   *  blueValue - 0-255
  */
  analogWrite(rLEDPin, redValue);
  analogWrite(gLEDPin, greenValue);
  analogWrite(bLEDPin, blueValue);
}

void turnServo(int posMicroseconds, int indicator=1, bool skip=false){
  /*turnServo - turns the servo and calls draw to repaint the OLED screen
   *
   * Parameters:
   * posMicroseconds - servo position in microseconds
   * [optional]indicator - passed value to the draw function
   * [optional]skip - calls the draw function after every 30 posMicroseconds
   */
  myServo.writeMicroseconds(posMicroseconds);          // Rotate Servo in microseconds

  //Skip overide - if it's close to min max values, don't skip
  if((posMicroseconds<=(minPos *1.001))||(posMicroseconds>=(maxPos *.999))){skip=false;}
    
  if (skip){                                                //May skip the draw function if true
    if (posMicroseconds%30==0) {
      draw(posMicroseconds, indicator);                     //skips the draw function if posMicroseconds is not evenly divisable by 30
    } else {
      delay(1);
    }
  } else {                                                  //call the draw function
    draw(posMicroseconds, indicator);
  }    
}

void serverRotate(bool turnLeft){
  /*serverRotate - Rotates the servo the range set by the
   *               the minimum Postion and maximum Postion
   *               Note: maxpos !> imax && minpos !< imin  
   *Parameters:               
   *turnLeft - provides the rotation direction
    */
  bool ledState = true;
  int pos;

  if (turnLeft) {                                          // rotate left
    Serial.println("One moment...Rotating left from 0 to 180");
    for (pos = minPos; pos <= maxPos; pos += 1) {          // goes from 0 degrees to 180 degrees using MS
      // in steps of 1 degree
      turnServo(pos,1,true);
      //Blinks the LED
      if (pos%60==0){
        setColor(maxBright*ledState,0,0);
        ledState=!ledState;
      }
    }
  } else {                                                // rotate Right
    Serial.println("One moment...Rotating right from 180 to 0");
    for (pos = maxPos; pos >= minPos; pos -= 1) {         // goes from 180 degrees to 0 degrees using MS
      turnServo(pos,1,true);
      //Blinks the LED
      if (pos%60==0){
        setColor(maxBright*ledState,0,0);
        ledState=!ledState;
      }
    }
  }
}

void doEncoder(){
  /*doEncoder - gets the rotary encoder values and adjusts
   *            the minPos or maxPos depending when user 
   *            initiates the adjustment mode
   */
  //Local Variables
  int pos = myServo.readMicroseconds();                   //Read current postion in microseconds
  int midPos = round((maxPos-minPos)/2);
  //Since the encoder can go faster than the function or servo
  pos += eCounter;                                        //Add eCounter to position
  eCounter = 0;                                           //reset eCounter
  
  if (pos <= midPos){                                     //Adjusting minimum
    if (pos>=imin) {                                      //checking pos size
      //Note servo function will not go less than original minPos
      minPos = pos;
      turnServo(pos,0);
    } else {                                              //Set to imin
       pos = imin;                                        //Set pos to imin
       turnServo(pos,0);
       Serial.print ("Already at minimum "); Serial.println(imin);
    }
  } else {                                                //Adjusting maximum
    if (pos<=imax){                                       //checking pos size
      //Note servo function will not go less than original maxPos
      maxPos = pos;
      //Serial.print("Changing maxPos to "); Serial.println(pos);
      turnServo(pos,2);        
    } else {                                              //Set pos to imax
      pos = imax;
      turnServo(pos,0);
      Serial.print ("Already at maximum "); Serial.println(imax);
    }
  } 
}

void eButton_isr(){
  // Encoder button Interrupt Service Routine using an interrupt
  ebutton = true;
}

// encoder_isr()
// Pin Change Interrupt Request 1 (pins A0 to A5)  (PCINT1_vect)
// This low level coding is used to handle a chnage for a group of pins
ISR (PCINT1_vect) {
  // handle pin change interrupt for A0 to A5 here
  //   the above ISR name is required
  //   this routine is one of the fastest ways to 
  //   to capture the quadrature movement in the 
  //   Encoder.  Using a single interrupt on pin 2  
  //   and half resolution would also be an option.
  /* Truth table
   * LastPinA | LastPinB | PinA | PinB | int | Rotate
   *     0          0       0      0   |  0  |   0
   *     0          0       0      1   |  1  |  -1
   *     0          0       1      0   |  2  |   1
   *     0          0       1      1   |  3  |   0
   *     0          1       0      0   |  4  |   1   
   *     0          1       0      1   |  5  |   0
   *     0          1       1      0   |  6  |   0
   *     0          1       1      1   |  7  |  -1   
   *     1          0       0      0   |  8  |  -1   
   *     1          0       0      1   |  9  |   0
   *     1          0       1      0   |  10 |   0
   *     1          0       1      1   |  11 |   1
   *     1          1       0      0   |  12 |   0
   *     1          1       0      1   |  13 |   1
   *     1          1       1      0   |  14 |  -1
   *     1          1       1      1   |  15 |   0
   */  
  static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t enc_val = 0;

  enc_val = enc_val << 2;                                   //Saves history

  /*Analog pins A0-A5
    PINC reads all the pins A0-A5 but in this order A5,A4,A3,A2,A1,A0
    That's why PinA is on A1 and PinB in on A0
    that way the bits are in the right order 0b11 = PinA PinB
    If you change order, you'll need to redo the truth table above.
    First we AND a bit mask to the pin read to hide the other pins: 0b11
    No shift needed since they're already the last two binary bits.
    Next we OR the new value with historical.  
    That gives us the truth table index value.  Slick!
  */
  enc_val = enc_val | (PINC & 0b11);     

  //  Again AND a bit mask to hide other values (old history),
  //  Remember a byte is 8 bits long.
  //  The index value from Table returns the movement
  eCounter += lookup_table[enc_val & 0b1111];
}  


