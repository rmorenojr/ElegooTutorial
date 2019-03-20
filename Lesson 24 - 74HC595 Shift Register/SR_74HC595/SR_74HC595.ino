/* ********************************************************************** 
 *  Shift Register 74HC595 with LEDs
 *
 * Inspired by Elegoo Lesson 24 
 *   www.elegoo.com     2016.12.9 
 * 
 * Circuit:
 * 
 *         LED  D12       D11
 *     5V   0   MISO GND  MOSI  D9  5V  
 *     |    |    |    |    |    |    |    |
 *  |--|----|----|----|----|----|----|----|--|
 *  |  VCC  Q0   DS  OE  ST_CP SH_CP MR  Q7' |
 *  |                                        |
 *  |  Q1   Q2   Q3  Q4    Q5   Q6   Q7  GND |
 *  |--|----|----|----|----|----|----|----|--| 
 *     |    |    |    |    |    |    |    |
 *    LED  LED  LED  LED  LED  LED  LED  GND
 *     1    2    3    4    5    6    7
 *
 * https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitset/
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
 ********************************************************************* */

/* ***************************************************
 *                Globsl Constants                   *
 *************************************************** */
int tDelay   = 100;
int dataPin  = 12;      //    DS - data serial on 74HC595
int latchPin = 11;      // ST_CP - storage register clock pin on 74HC595
int clockPin = 9;       // SH_CP - shift register clock pin on 74HC595 - Why not D13 SCK pin?

/* ***************************************************
 *                Globsl Variables                   *
 *************************************************** */
bool DirectionState = 0;

/* ***************************************************
 *                   Functions                       *
 *************************************************** */
void updateShiftRegister(byte leds){
    digitalWrite(latchPin, LOW);
    if (DirectionState == false) {
        shiftOut(dataPin, clockPin, LSBFIRST, leds);
    } else {
        shiftOut(dataPin, clockPin, MSBFIRST, leds);
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
    byte leds = 0B00000000;
    updateShiftRegister(leds);
    delay(tDelay);

    for (int i = 0; i < 8; i++){
        // set the bit i to 1, starting with bit 0, the least significant bit (rightmost bit)
        bitSet(leds, i);
        updateShiftRegister(leds);
        delay(tDelay);
    }
    DirectionState = !DirectionState;
}

