/* ***********************************************************
 * Sound Sensor sketch - v1.1
 *   Uses the KY-038 module
 *   Uses the U8g2lib.h library
 *
 * Inpired by Elegoo Lesson 20, and Arduino Sound meter
 *   by learnelectronics www.youtube.com/c/learnelectronics
 *
 * Description:
 *   This sketch illustrates some of the Sound Sensor Module 
 *   analog and digital features.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  History:
 *  01/02/2019 v1.0 - Initial release
 *  01/05/2019 v1.1 - removed str_len &dtosrtf from drawMeter
 *                    function. sprintf function does it all 
 *
 * @author Ricardo Moreno
 ********************************************************** */ 

/* ***********************************************************
 *                         Libraries                         *
 * ********************************************************* */
    #include <U8g2lib.h>

/* ***********************************************************
 *                      Global Constants                     *
 *                    Hardware Definitions                   *
 * ********************************************************* */
    // OLED Pins
    // A byte can hold a number up to 255
    const PROGMEM int OLED_CLK = 13;           // SCK system clock or SCL
    const PROGMEM int OLED_MOSI = 11;          // MOSI or SDA
    const PROGMEM int OLED_RES = 8;            // Reset
    const PROGMEM int OLED_DC = 7;             // Data Communication
    const PROGMEM int OLED_CS = 6;             // Component Select

    //Instantiate U8G2 object class - Plus Pins
    //SH1106
    U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);

    // Other hardware pins
    const PROGMEM int ledPin = 5;               // define LED
    const PROGMEM int digitalPin = 3;           // define Sensor's D0 pin
    const PROGMEM int analogPin = A0;           // define Sensor's A0 pin
   
/* ***********************************************************
 *                      Global Constants                     *
 * ********************************************************* */
    // https://github.com/olikraus/u8g2/wiki/u8g2reference
    #define largeFont u8g2_font_courB18_tf
    #define mainFont u8g2_font_courB14_tf
    const PROGMEM int screenWidth=128;
    const PROGMEM int screenHeight=64;
    const char *sketchTitle[] = {"Arduino", "Sound", "Sensor", "Calibrator"};
    const int sketchTitleArrayLength = 4;       // manually set for above array
    const int delayTime = 1000;                 // time in milliseconds
 
/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
    unsigned long previousMillis = 0;
    bool ledState = LOW;

    //To keep track of two different font sizes
    int largeFont_RowHeight;
    int mainFont_RowHeight;  
    
/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup(){
    Serial.begin (9600);
    pinMode(ledPin, OUTPUT);                   // define LED as output
    pinMode(digitalPin,INPUT);                 // define sensor D0 as input

    //OLED Diplay - Note this is using the full buffer which uses a lot of memory
    oled.begin();
    oled.clear();
    oled.setBitmapMode(1);                     // 1 = object background transparent
    oled.setDrawColor(1);                      // set the color

    //Initialize Fonts sizes
    // Large Font
    oled.setFont(largeFont);         
    int Ascent = oled.getAscent();            // getAscent returns the number of pixels above the baseline
    int Descent = -oled.getDescent();         // getDescent returns a negative value, a number of pixels below the baseline 
    largeFont_RowHeight = Ascent+Descent+1;
    // Main Font
    oled.setFont(mainFont);                   // https://github.com/olikraus/u8g2/wiki/u8g2reference 
    Ascent = oled.getAscent();                // getAscent returns the number of pixels above the baseline
    Descent = -oled.getDescent();             // getDescent returns a negative value, a number of pixels below the baseline 
    mainFont_RowHeight = Ascent+Descent+1;

    // Display Title
    int rowPosition = mainFont_RowHeight-1;   // Start from rowPosition 0
    for (int x=0; x<sketchTitleArrayLength; x++){
      int colPosition = int(((screenWidth - oled.getStrWidth(sketchTitle[x]))/2.0));
      //begin Debug lines
          Serial.print("Row Position = ");Serial.print(rowPosition);
          Serial.print(" Column Pos = ");Serial.print(colPosition);
          Serial.print(" ");Serial.println(sketchTitle[x]);
      //end Debug lines
      oled.setCursor(colPosition,rowPosition); // Position Cursor
      oled.print(sketchTitle[x]);              // write title
      rowPosition += mainFont_RowHeight;       // Set for next row
    }
    oled.sendBuffer();
    delay(2000);                               // wait 2 seconds
}
 
/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop(){
    checkAnalog();
    checkDigital();
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */
void drawMeter(float fvalue, float fminValue, float fmaxValue, char unit = 'V'){
    /* drawMeter creates the meter or gauge on the OLED display with
     *           min & max values and tick marks
     *   Parameters:    
     *   fvalue    - the value concatinated with unit displayed top  
     *               center in large font    
     *   fminValue - the minimum value, displayed on the left
     *   fmaxValue - the maximum value, displayed on the right
     *   [optional]unit - the unit of measurement
     */

    int colPosition;                             // column position or x-coordinate
    int rowPosition;                             // row position or y-coordinate
    //unsigned int str_len = 0;
    char cArray[11];                             // max size 99999999.99 or 999999.99 V
    
    /** ---------    meter Gauge Values     --------**/    
    //screenWidth = 128;
    //screenHeight = 64
    int meterWidth = (screenWidth/5)/2*2*5;      // 120
    int meterStart = (screenWidth-meterWidth)/2; // (128-120)/2=4
    int meterHeight = 10;
    int radius = meterHeight/2-2;                // r < H/2-1
    int majorTickMarkLenth = 6;
    int minorTickMarkLength = 2;
    int minmaxTickMarkLength = 6;
    int majorTickSpacing = meterWidth/5;         // 5 major tick mark plus zero
    int minorTickSpacing = meterWidth/20;        // 

    oled.clearBuffer();                          // clear the display

    // Convert float to char array and add unit char
    sprintf(cArray, "%*.2f %c", fvalue, unit);
     
    /** ---------      Display Main Value          --------**/
    oled.setFont(largeFont);                    // Set the font size
    //Calculate to center text
    colPosition = int(((screenWidth - oled.getStrWidth(cArray))/2.0));
    rowPosition = largeFont_RowHeight -1;
    oled.setCursor(colPosition,rowPosition);    // Start text at the top of screen
    oled.print(cArray);                         // write calibrated decibels
    
    /** ---------        Draw Min Max Ticks        --------**/
    oled.setFont(mainFont);                    // Set the font size
    // minVolt text
    colPosition = 1;
    rowPosition = rowPosition + mainFont_RowHeight + 4;
    oled.setCursor(colPosition, rowPosition);
    oled.print(fminValue);
    // minVolt Tick mark
    // map(value, fromLow, fromHigh, toLow, toHigh)
    colPosition = map(fminValue*100.0, 0, 500, meterStart, meterWidth+meterStart);                
    oled.drawLine(colPosition, screenHeight-meterHeight-majorTickMarkLenth, colPosition, screenHeight-meterHeight-majorTickMarkLenth-minmaxTickMarkLength);

    // maxVolt text
    // Convert float to char array
    sprintf(cArray, "%*.2f", fmaxValue);
    colPosition = int((screenWidth - oled.getStrWidth(cArray) -1));
    oled.setCursor(colPosition, rowPosition);
    // maxVolt Tick mark
    oled.print(fmaxValue);
    colPosition = map(fmaxValue*100.0, 0, 500, meterStart, meterWidth+meterStart);                
    oled.drawLine(colPosition, screenHeight-meterHeight-majorTickMarkLenth, colPosition, screenHeight-meterHeight-majorTickMarkLenth-minmaxTickMarkLength);
    
    /** ---------          Draw Volt meter          --------**/
    //major tick marks
    for(int x = meterStart; x < screenWidth; x += majorTickSpacing){          
      oled.drawLine(x, screenHeight-meterHeight, x, screenHeight-meterHeight-majorTickMarkLenth);
    }
    //minor tick marks
    for(int x = meterStart+minorTickSpacing; x < meterWidth+meterStart; x += minorTickSpacing){          
      oled.drawLine(x, screenHeight-meterHeight, x, screenHeight-meterHeight-minorTickMarkLength);
    }
    // draw outline of bar graph    
    oled.drawRFrame(meterStart-1, screenHeight-meterHeight, meterWidth+2, meterHeight, radius);
             
    // draw voltage bar length
    int barLength = map(fvalue*100.0, 0, 500, meterStart, meterWidth+meterStart);                
    oled.drawRBox(meterStart, screenHeight-meterHeight+1, barLength, meterHeight-2, radius-1);

    oled.sendBuffer();    
}

void checkAnalog(){
    /* checkAnalog reads analog pin, saves min & max values, calculates voltages
     *   Parameters: (none)
     *   calls: drawMeter
     */
    static int maxA = 0;                        // max analog value
    static int minA = 1023;                     // min analog value
    int aValue = 0;                             // raw analog value
    float volts;                                // analog voltage value
    float maxvolts;                             // max voltage value
    float minvolts;                             // min voltage value
                                       
    aValue = analogRead(analogPin);             // analog values from 0-1023, 5V max

    if (aValue < minA) { minA = aValue;}        // save new min value
    if (aValue > maxA) { maxA = aValue;}        // save new max value
    volts = (aValue*5.0)/1024.0;
    minvolts = (minA*5.0)/1024.0;
    maxvolts = (maxA*5.0)/1024.0;

    // begin Debug code - Serial print analog value as decimal
        Serial.print("A = "); Serial.print(aValue,DEC);
        Serial.print(" Max = "); Serial.print(maxA);
        Serial.print(" Min = "); Serial.print(minA);
        Serial.print(" volts = "); Serial.println(volts);
    // end Debug code

    drawMeter(volts, minvolts, maxvolts,'V');
}

void checkDigital(){
    /* checkDigital reads the digital pin and sets LED state if delay time has expired
     *   Parameters: (none)   
     */
    bool dValue = HIGH;                                 // variable to store digital value
    unsigned long currentMillis = millis();
    
    dValue = digitalRead(digitalPin);           // digital value from D0
    // begin Debug code
        //if (dValue==LOW) Serial.println("Digital Pin reads LOW");
    // end Debug code 
    if(((currentMillis - previousMillis) > delayTime) && (dValue == LOW)){
    //if(dValue == LOW){
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        previousMillis = currentMillis;
    } 
}
