/* ********************************************************************** 
 * 7-SegmentDisplay - v1.0
 *   Uses Common cathode 7-segment display,
 *   Uses 74HC595 shift register IC
 *   
 * Inspired by Elegoo Lesson 27 www.elegoo.com
 *   modified by Ricardo Moreno
 *
 * Description:
 *   This sketch illustrates the controlling a 7-segment display with
 *   a 74HC595 shift register.
 *   
 *  History:
 *  5/04/2019 v1.0 - Initial release
 *  
 * define the LED digit patterns, from 0 - 9
 * 1 = LED on, 0 = LED off, common cathode, in this order:
 *           74HC595 pin     Q7,Q6,Q5,Q4,Q3,Q2,Q1,Q0 
 *           Mapping to      g,f,e,d,c,dp,a,b of Seven-Segment LED
 * ********************************************************* */
 /* ***********************************************************
 *                      Global Constants                     *
 *                    Hardware Definitions                   *
 * ********************************************************* */
int latchPin = 11; // connect to the ST_CP of 74HC595 (pin 3,latch pin)
int clockPin = 9;  // connect to the SH_CP of 74HC595 (pin 4, clock pin)
int dataPin = 12;  // connect to the DS of 74HC595 (pin 2)

byte sevenSegDigits[10] = { B01111011   ,  // = 0
                            B00001001   ,  // = 1
                            B10110011   ,  // = 2
                            B10011011   ,  // = 3
                            B11001001   ,  // = 4
                            B11011010   ,  // = 5
                            B11111000   ,  // = 6
                            B00001011   ,  // = 7
                            B11111011   ,  // = 8
                            B11001011      // = 9
                           };
byte sevenSegDP = B00000100;  // = DP

byte sevenSegAlpha[] = {  B11101011   , // = A
                          B11111000   , // = b
                          B01110010   , // = C
                          B10111001   , // = d
                          B11110010   , // = E
                          B11100010   , // = F
                          B11011011   , // = g
                          B11101000   , // = h
                          B01100000     // = I   
};
/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
bool bAddDecimalPoint = true;            // display state of show decimal point

/* ***********************************************************
 *                         Void setup                        *
 * ********************************************************* */
void setup() {
    // Set latchPin, clockPin, dataPin as output
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */ 
// display a alpha, binary value, or number on the digital segment display
void sevenSegWrite(byte digit, bool bDP = false, char switchValue='D') {
    /*       digit = array pointer or binary value, as a byte 
     *         bDP = true-include decimal point, as boolean
     * switchValue = 'A' alpha
     *               'B' binary
     *               'D' digits <default>, as char           */
    
    // set the latchPin to low potential, before sending data
    digitalWrite(latchPin, LOW);
     
    // the data (bit pattern)
    if (switchValue=='A'){
        // alpha
        shiftOut(dataPin, clockPin, MSBFIRST, sevenSegAlpha[digit]+(sevenSegDP*bDP)); 
    } else if (switchValue=='B'){
        // binary
        shiftOut(dataPin, clockPin, MSBFIRST, digit+(sevenSegDP*bDP));
    } else {
        // digits
        shiftOut(dataPin, clockPin, MSBFIRST, sevenSegDigits[digit]+(sevenSegDP*bDP));   
    }
 
    // set the latchPin to high potential, after sending data
    digitalWrite(latchPin, HIGH);
}

void sevenSegBlank(){
    // set the latchPin to low potential, before sending data
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);  
    // set the latchPin to high potential, after sending data
    digitalWrite(latchPin, HIGH);
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop() {
    //Switch add decimal point states
    bAddDecimalPoint = !bAddDecimalPoint;       
    // count from 9 to 0
    // Change byte to int - byte doesn't have a negative number
    for (int digit = 9; digit >= 0; --digit) {
        sevenSegWrite(digit, bAddDecimalPoint);
        delay(1000);
    }
    // suspend 1 second
    sevenSegBlank();
    delay(1000);
  
    // count from 0 to 9
    for (int digit = 0; digit <= 9; digit++) {
        sevenSegWrite(digit, bAddDecimalPoint);
        delay(1000);
    }
    // suspend 1 second
    sevenSegBlank();
    delay(1000);
  
    // alpha characters
    for (int digit = 0; digit <= 8; digit++){
        sevenSegWrite(digit, bAddDecimalPoint, 'A');
        delay(1000);
    }
    // suspend 1 second
    sevenSegBlank();
    delay(1000);

    // display individual segments - Binary
    sevenSegWrite(1,false,'B');    // B00000001
    delay(1000);
    sevenSegWrite(2,false,'B');    // B00000010
    delay(1000);
    sevenSegWrite(4,false,'B');    // B00000100
    delay(1000);
    sevenSegWrite(8,false,'B');    // B00001000
    delay(1000);
    sevenSegWrite(16,false,'B');   // B00010000
    delay(1000);
    sevenSegWrite(32,false,'B');   // B00100000
    delay(1000);
    sevenSegWrite(64,false,'B');   // B01000000
    delay(1000);
    sevenSegWrite(128,false,'B');  // B10000000
    delay(1000);

    // SECRET MESSAGE
    sevenSegWrite(0xE8,false,'B');  // B11101000
    delay(500);
    sevenSegWrite(0xF2,false,'B');  // B11110010
    delay(500);
    sevenSegWrite(0x70,false,'B');  // B01110000
    delay(500);
    sevenSegBlank();                // small blank flick
    delay(100);
    sevenSegWrite(0x70,false,'B');  // B01110000
    delay(500);
    sevenSegWrite(0xB8,false,'B');  // B10111000
    delay(500);
    sevenSegBlank();
    delay(500);
    sevenSegWrite(0xD9,false,'B');  // B11011001
    delay(500);
    sevenSegWrite(0xB8,false,'B');  // B10111000
    delay(500);
    sevenSegWrite(0x38,false,'B');  // B00111000
    delay(500);
    sevenSegWrite(0xF0,false,'B');  // B11110000
    delay(500);
    sevenSegWrite(0x38,false,'B');  // B00111000
    delay(500);
    sevenSegWrite(0xF8,false,'B');  // B11111000
    delay(500);
    sevenSegWrite(0xF2,true,'B');   // B11110010
    delay(500);
    
    // suspend 1 second
    sevenSegBlank();
    delay(1000);
}
