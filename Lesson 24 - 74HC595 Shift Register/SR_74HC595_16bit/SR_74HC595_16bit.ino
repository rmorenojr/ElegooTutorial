/* ********************************************************************** 
 * Shift Register 74HC595 with 16 LEDs
 *   back to back shift registers
 *   
 * Inspired by Elegoo Lesson 24 
 *   www.elegoo.com     2016.12.9 
 * 
 * Circuit:
 *                                        ____________________
 *         LED  D12       D11             |            LED   |        D11
 *     5V   0   MISO GND  MOSI  D9   5V   |        5V   8    |   GND  MOSI  D9   5V  
 *     |    |    |    |    |    |    |    |        |    |    |    |    |    |    |    |
 *  |--|----|----|----|----|----|----|----|--|  |--|----|----|----|----|----|----|----|--|
 *  |  VCC  Q0   DS  OE  ST_CP SH_CP MR  Q7' |  |  VCC  Q0   DS  OE  ST_CP SH_CP MR  Q7' |
 *  |                                        |  |                                        |
 *  |  Q1   Q2   Q3  Q4    Q5   Q6   Q7  GND |  |  Q1   Q2   Q3  Q4    Q5   Q6   Q7  GND |
 *  |--|----|----|----|----|----|----|----|--|  |--|----|----|----|----|----|----|----|--| 
 *     |    |    |    |    |    |    |    |        |    |    |    |    |    |    |    |
 *    LED  LED  LED  LED  LED  LED  LED  GND      LED  LED  LED  LED  LED  LED  LED  GND
 *     1    2    3    4    5    6    7             9    10   11   12   13   14   15
 *
 * https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitset/
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
 ********************************************************************* */

/* ***************************************************
 *                Global Constants                   *
 *************************************************** */
const int tDelay   = 100;     // delay between LED switching 
const int dataPin  = 12;      //    DS - data serial
const int latchPin = 11;      // ST_CP - storage register, latch clock pin
const int clockPin = 9;       // SH_CP - shift register clock pin

/* ***************************************************
 *                Global Variables                   *
 *************************************************** */
bool DirectionState = 0;

/* ***************************************************
 *                   Functions                       *
 *************************************************** */
void updateShiftRegister(unsigned int leds, bool isMSBFIRST = true){
    /*  Performs all the necessary work to serial load 
     *    two shift registers.  Direction controlled by 
     *    isMSBFIRST
     *  Paramters:
     *    leds       - insigned 16-bit number {required} 
     *    isMSBFISRT - boolean for direction 
     *                 true  = MSBFIRST
     *                 false = LSBFIRST
     *  called by void loop                           */           

    /*         Local variables            */ 
    /* example:    Higher byte Lower byte
     *  16-bit word = 00000000 00000000   */
    byte lowLED  = lowByte(leds);      // extacts the lower byte, right most byte, from a 16-bit word or unsigned integer
    byte highLED = highByte(leds);     // extracts the higher byte, left most byte, from a 16-bit word or unsigned integer

    digitalWrite(latchPin, LOW);
    if (isMSBFIRST == false) {
        // LEDs move from right to left
        shiftOut(dataPin, clockPin, LSBFIRST, lowLED);   // shiftout only works with a byte value
        shiftOut(dataPin, clockPin, LSBFIRST, highLED);  
    } else {
        // LEDs move from left to right
        shiftOut(dataPin, clockPin, MSBFIRST, highLED);
        shiftOut(dataPin, clockPin, MSBFIRST, lowLED);
    }
    digitalWrite(latchPin, HIGH);
}

/* ***************************************************
 *                   Void Setup                      *
 *************************************************** */
void setup(){
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin,  OUTPUT);  
    pinMode(clockPin, OUTPUT);
}

/* ***************************************************
 *                   Void Loop                       *
 *************************************************** */
void loop(){
    unsigned int leds = 0B0000000000000000;
    updateShiftRegister(leds);
    delay(tDelay);

    for (int i = 0; i < 16; i++){
        // set the bit i to 1, starting with bit 0, the least significant bit (rightmost bit)
        leds = 0B0000000000000000;
        bitSet(leds, i);
        updateShiftRegister(leds, DirectionState);
        delay(tDelay);
    }
    DirectionState = !DirectionState;
}
