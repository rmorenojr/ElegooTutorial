/* ********************************************************************** 
 * Four Digit Hex Counter
 *   Uses: one 74HC595 shift register
 *         one four digit seven segment display - common cathode (5641AS)
 *         four PN2222 transistors
 *   
 * Inspired by Elegoo Lesson 28 
 *   www.elegoo.com     2016.12.12
 *   modified by Ricardo Moreno
 *
 * Description:
 *   This sketch illustrates controlling a four digit 7-segment 
 *   display with a single 74HC595 shift register. Elegoo kit only
 *   has one 74HC595, so the Arduino will control 7-segment pins D1-D4. 
 *   
 *  History:
 *  6/06/2019 v1.0 - Initial release
 *  
 *  Verify circuit connections:
 *           74HC595 pin     Q7,Q6,Q5,Q4,Q3,Q2,Q1,Q0 
 *           Mapping to       g, c,DP, d, e, b, f, a (7-Segment LED)
 *           for array purposes D4 = digit0, etc.
 ********************************************************************* */

/* ***************************************************
 *                Global Constants                   *
 *************************************************** */
 
const int dataPin  = 12;  // 74HC595 pin 8 DS
const int latchPin = 11;  // 74HC595 pin 9 STCP
const int clockPin = 9;   // 74HC595 pin 10 SHCP
const int digit0   = 7;   // 7-Segment pin D4
const int digit1   = 6;   // 7-Segment pin D3
const int digit2   = 5;   // 7-Segment pin D2
const int digit3   = 4;   // 7-Segment pin D1 

/* ***************************************************
 *                Global Variables                   *
 *************************************************** */
// Hex values reference which LED segments are turned on
// and may vary from circuit to circuit.  Note the mapping above.
byte table[]= 
    {   0x5F,  // = 0
        0x44,  // = 1
        0x9D,  // = 2
        0xD5,  // = 3
        0xC6,  // = 4
        0xD3,  // = 5
        0xDB,  // = 6
        0x45,  // = 7
        0xDF,  // = 8
        0xC7,  // = 9
        0xCF,  // = A
        0xDA,  // = b
        0x1B,  // = C
        0xDC,  // = d
        0x9B,  // = E
        0x8B,  // = F
        0x00   // blank
    };  //Hex shown
byte digitDP = 32;  // 0x20 - adds this to digit to show decimal point
byte controlDigits[] = { digit0, digit1, digit2, digit3 };  // pins to turn off & on digits
byte displayDigits[] = { 0,0,0,0,0 }; // ie: { 1, 0, 7, 13, 0} == d701 (all values from table array)
    /* Each array value holds digit values as table array index, or raw byte
     *  parameters: digit0, digit1, digit2, digit3, digitSwitch
     *  
     * digitSwitch: the four least significant bits controls data handling, 
     *              each bit controls associated digit
     *              starting with least-significant bit 0, 
     *              i.e. B1010, digit1 & digit3 are raw, 
     *                          digit0 & digit2 use table array 
     *       1 = raw byte
     *       0 = table array index                                         */  
unsigned long onTime = 0;             // tracks time
bool switchView = false;              // switch between HexCounter (table array) and RawDisplay (raw bytes)
                                      //    false = HexCounter
                                      //     true = RawDisplay
unsigned int counter = 0;             // RawDisplay counter

/* ***************************************************
 *           Global Adjustable Variables             *
 *************************************************** */
int digitDelay = 50;                  // delay between incrementing digits (ms)
int brightness = 90;                  // valid range of 0-100, 100=brightest
unsigned int ShowSegCount = 250;      // number of RawDisplay loops before switching again 
//bool commonCathode = true;

/* ***************************************************
 *                   Void Setup                      *
 *************************************************** */
void setup() {
    //DDRD=0xff;                      // make pins 0-7 outputs
    //DDRB=0xff;                      // make pins 8-13 outputs
    //PORTD=0xf0;                     // make pins 4-7 HIGH
    
    pinMode(latchPin,OUTPUT);
    pinMode(clockPin,OUTPUT);
    pinMode(dataPin,OUTPUT);
    for (int x=0; x<4; x++){
        pinMode(controlDigits[x],OUTPUT);
        digitalWrite(controlDigits[x],LOW);  // Turns off the digit  
    }
}

/* ***************************************************
 *                   Functions                       *
 *************************************************** */    
void DisplaySegments(){
    /* Display will send out all four digits
     * one at a time.  Elegoo kit only has 1 74HC595, so
     * the Arduino will control the digits
     *   displayDigits[4] = the right nibble controls output type
     *                      1 = raw, 0 = table array
     *                  upper (left) nibble ignored
     *                  starting with 0, the least-significant (rightmost) bit
     */
    
    for (int x=0; x<4; x++){
        for (int j=0; j<4; j++){
            digitalWrite(controlDigits[j],LOW);    // turn off digits
        }
        digitalWrite(latchPin,LOW);
        if (bitRead(displayDigits[4],x)==1){
            // raw byte value is sent to shift register
            shiftOut(dataPin,clockPin,MSBFIRST,displayDigits[x]);
        } else {
            // table array value is sent to the shift register
            shiftOut(dataPin,clockPin,MSBFIRST,table[displayDigits[x]]);
        }
        
        digitalWrite(latchPin,HIGH);
        digitalWrite(controlDigits[x],HIGH);   // turn on one digit
        delay(1);                              // 1 or 2 is ok
    }
    for (int j=0; j<4; j++){
        digitalWrite(controlDigits[j],LOW);    // turn off digits
    }
}

void HexCounter(){
    /* Increments values stored in displayDigits array to
     * creates a Hex counter from the table array.
     * Uses mixed display types:
     *    Digit3 | Digit2 | Digit1 | Digit0 
     *    ---------------------------------
     *       C   |   0    |   0    |    0
     */
    byte Letter = B00011011;  // C
     
    //increment values for digits 0-2
    bool incrementValue = true;
    for (int d = 0; d < 3; d++){
        int x = int(displayDigits[d]);
        if (incrementValue == true) {
            x++;
            incrementValue = false;
            if (x > 15) {
                displayDigits[d] = 0;
                incrementValue = true;
            } else {
                displayDigits[d] = byte(x);
            }
        }
    }
    // Set digit3 value
    displayDigits[3] = Letter;
    // Set digitSwitch option
    displayDigits[4] = B1000;
    
    if ((displayDigits[0] == 0)&&(displayDigits[1] == 0)&&(displayDigits[2] == 0)){
        switchView = !switchView;
        for(int x = 0; x < 5; x++){ displayDigits[x]=0; }        // Reset array
        displayDigits[4] = B0000;
    }
}

void RawDisplay(){
    // HALO
    displayDigits[0] = B01011111;  // 0
    displayDigits[1] = B00011010;  // L
    displayDigits[2] = B11001111;  // A
    displayDigits[3] = B11001110;  // H
     // Set digitSwitch option
    displayDigits[4] = B1111;
    
    if (counter < ShowSegCount){ 
        counter++;
    } else {
        // Reset everything
        counter = 0;
        switchView = !switchView;
        for(int x =0; x<5; x++){ displayDigits[x]=0; }        // Reset array
        displayDigits[4] = B0000;
    }
}

/* ***************************************************
 *                   Void Loop                       *
 *************************************************** */
void loop() {

    DisplaySegments();                                      // Caution: Avoid extra delays
    
    /* *************************************
     *         Control Brightness          *
     * *********************************** */
    delayMicroseconds(1638*((100-brightness)/10));         // largest value 16383
    
    /* *************************************
     *        Selects Display Type         *
     * *********************************** */
    unsigned long nowValue = millis() - onTime;
    if (nowValue >= long(digitDelay)){
        onTime = millis();
        if(switchView==true){ RawDisplay(); } else { HexCounter(); }
    }
}
