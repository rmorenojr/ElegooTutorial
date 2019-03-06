/* ***********************************************************
 *  Thermometer
 *   uses the LiquidCrystal.h Library
 *   <optional> uses LiquidCrystal_I2C.h
 *
 *  Inspired by Elegoo Lesson 23 and
 *  Measuring Temperature with an NTC Thermistor by all about circuits
 *  https://www.allaboutcircuits.com/projects/measuring-temperature-with-an-ntc-thermistor/
 *  
 *  The circuit:
 *         5v ----\/\/\/-------|-------\/\/\/---- GND
 *             R_thermistor    |         R_2 
 *                             |
 *                        Analog Pin A0
 *                                 
 *   Ardino
 *   UNO:        10K POT                               220-ohms
 *           5V --\/\/\/--- GND                     5V --\/\/\/-|
 *                  | wiper                                     |       
 *                  |                                           |
 *   Uno:  GND  5V  |   12  11                  5   4   3   2   |  GND
 *         -|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
 *   LCD:  VSS VDD  V0  RS  E   D0  D1  D2  D3  D4  D5  D6  D7  A   K
 *
 * Description:
 *   This sketch illustrates the Thermistor using a smoothing techique
 *   and the LCD.
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
 *  02/24/2019 v1.0 - Initial release
 *
 * ********************************************************* */

/* ***********************************************************
 *                         Libraries                         *
 * ********************************************************* */
    #include <LiquidCrystal.h>                         // Standard LCD library
    //#include <LiquidCrystal_I2C.h>                   // I2C LCD Library

/* ***********************************************************
 *                      Global Constants                     *
 *                    Hardware Definitions                   *
 * ********************************************************* */
    // Standard LCD pin connection
    const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7);         // instantiate lcd
    // I2C LCD connection
    //LiquidCrystal lcd(0x3F, 16, 2);                  // LCD address, #columns, #rows
    
    const int thermistorPin = A0;                      // Thermistor pin
    const float Resistor2 = 10000.0;                   // R2 resistor Value
    const int SampleNumber = 30;                       // The number of analog samples (30 max for integer)
    const int aMax = 1023;                             // Maximum Analog value 1023
    const float t25 = 25.0+273.15;                     // Temperature in Kelvin at 25C
    const float r25 = 10000.0;                         // Thermistor resistance at 25C
    const float Beta = 3950.0;                         // Thermistor Beta from the datasheet
    //Steinhart-Hart Coefficient values - calculated
    const float scA =  0.00102219653793705;
    const float scB =  0.000253179116444952;
    const float scC = -0.000000000058799201163101;

/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
    int aValues[SampleNumber];                        // Analog value Array 
    int index = 0;                                    // Tracks the array index
    int total = 0;                                    // Keeps a running total
  
/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup() {
    /* **********************************
     *  Normal begin statement for LCD  *
     *  (#columns, #rows)               *
     ********************************** */
    lcd.begin(16, 2);                                 // Direct wire statement
    /* **********************************
     *  I2C begin statements            *
     ********************************** */
    //lcd.begin();                                    // I2C statement
    //lcd.backlight();                                // Turn on the blacklight
    
    // Reset or initialize array
    int aValue = analogRead(thermistorPin);           // Get inital analog value seed
    for(int x=0; x<SampleNumber; x++){aValues[x]=aValue;}
    total = aValue * SampleNumber;
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop() {
    float tCelsius = readThermistor();                // returns Celsius value    
    displayTemperature(tCelsius);                     // Display temperature value
    delay(1000);                                      // Small delay before repeating
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */
float readThermistor(){
    // Uses a smoothing technique
    total = total - aValues[index];                   // Subtract the last reading

    aValues[index] = analogRead(thermistorPin);       // Get analog value
    total = total + aValues[index];                   // Running total
    index += 1;                                       // Increment index
    if (index >= SampleNumber){index = 0;}            // Reset index if >= SampleNumber
    float Average = float(total) / float(SampleNumber);           // Calculate average
    float rThermistor = Resistor2 * (float(aMax)/Average - 1.0);  // Thermistor resistance
    float tKelvin = 1.0/(scA + scB * log(rThermistor) + scC * (pow(log(rThermistor),3)));
    float tCelsius = tKelvin - 273.15;                // Convert Kelvin to Celsius
    return(tCelsius);
  
    //tKelvin = 1 / (0.001129148 + 0.000234125 * log(rThermistor) + 0.0000000876741 * pow(log(rThermistor),3)));
    // where A = 0.001129148, B = 0.000234125, and C = 0.0000000876741
    // how were these calculated?
}

void displayTemperature(float tCelsius){
    float tFahrenheit = (tCelsius * 9.0)/ 5.0 + 32.0;  // Calculate Fahrenheit
    
    // Display Temperature in C
    lcd.setCursor(0, 0);                               // First row
    lcd.print("Temp         C  ");                     // Updates and clear display row
    lcd.setCursor(12, 0);                              // Locate degree symbol
    lcd.print((char)223);                              // prints the degree symbol
    lcd.setCursor(6, 0);                               // Locate temperature
    lcd.print(tCelsius);
    // Display Temperature in F
    lcd.setCursor(0, 1);                               // Second Row
    lcd.print("             F  ");                     // Updates and clear display row
    lcd.setCursor(12, 1);                              // Locate degree symbol
    lcd.print((char)223);                              // prints the degree symbol
    lcd.setCursor(6, 1);                               // Locate temperature
    lcd.print(tFahrenheit);     
}
