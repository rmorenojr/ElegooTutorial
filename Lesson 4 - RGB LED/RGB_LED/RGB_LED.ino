/* ***********************************************************
 * RGB_LED sketch - v1.0
 *   Uses common cathode RGB LED
 *   Arduino UNO R3
 *   
 * Inspired by Elegoo Lesoon 4 - RGB LED
 *   Included with The Most Complete Starter Kit by Elegoo
 *   Original by - HowToMechatronics.com and Elegoo.com
 *   Modified by - Ricardo Moreno
 *  
 * Description:
 *   This sketch illustrates a few ways to control the RGB LED
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
 *    1/5/2018 - v1.0 initial release
 *  12/30/2019 - Minor comment and indent revisions to
 *               improve readability. Moved Function setColor 
 *               to the top of the sketch. Renamed delayTime
 *               to longDelay.
 *       
 * ********************************************************* */

/* ***********************************************************
 *                      Global Constants                     *
 *                    Hardware Definitions                   *
 * ********************************************************* */
    /* The Arduino Web site recommends that one uses const 
     * rather than #define since using #define could have  
     * unwanted side effects
     */
    const int    redPin = 6;   // Red LED pin
    const int  greenPin = 5;   // Green LED pin
    const int   bluePin = 3;   // Blue LED pin
    const int maxBright = 255; // Maximum LED brightness

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */
void setColor(int redValue, int greenValue, int blueValue){
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
    Serial.print("Red: ");
    Serial.print(redValue);
    Serial.print(" Green: ");
    Serial.print(greenValue);
    Serial.print(" Blue: ");
    Serial.println(blueValue);
}

/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup(){
    Serial.begin(9600);       //Turn On the Serial Port
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop(){
    //Local Variables
    int longDelay = 1000;   // fading time between colors
    int shortDelay = 10;    // short time delay between colors
    int redValue;
    int greenValue;
    int blueValue;
    int ledGear;            // For switching LED fading 
    
    //I combined various ways to turn on the RGB LED
    //Here we manually set the color
    Serial.println("Manual Colors");
    setColor(maxBright, 0, 0);                  //Red Color
    delay(longDelay);
    setColor(0, maxBright, 0);                  //Green Color
    delay(longDelay);
    setColor(maxBright, maxBright, maxBright);  //White Color
    delay(longDelay);
    setColor(170, 0, maxBright);                //Purple Color
    delay(longDelay);
    
    Serial.println("Fade from Red to Green");
    //Fade from Red to Green
    delay(longDelay);
    redValue = maxBright;
    greenValue = 0;
    blueValue = 0;
    for(int i = 0; i < maxBright+1; i++){
        setColor(redValue, greenValue, blueValue);
        redValue -= 1;
        greenValue += 1;
        delay(shortDelay);
    }
    
    Serial.println("Fade from Green to Blue");
    //Fade from Green to Blue
    delay(longDelay);
    redValue = 0;
    greenValue = maxBright;
    blueValue = 0;
    for(int i = 0; i < maxBright+1; i++){
        setColor(redValue, greenValue, blueValue);
        greenValue -= 1;
        blueValue += 1;
        delay(shortDelay);
    }
    
    Serial.println("Fade from Blue to Red");
    //Fade from Blue to Red
    delay(longDelay);
    redValue = 0;
    greenValue = 0;
    blueValue = maxBright;
    for(int i = 0; i < maxBright+1; i++){
        setColor(redValue, greenValue, blueValue);
        blueValue -= 1;
        redValue += 1;
        delay(shortDelay); 
    }
    
    Serial.println("Fade All three colors Red to Green, Green to Blue, Blue to Red");
    //Fade All three colors Red to Green, Green to Blue, Blue to Red
    delay(longDelay);
    redValue = maxBright;
    greenValue = 0;
    blueValue = 0;
    ledGear = 1;
    do {
        setColor(redValue, greenValue, blueValue);
        //First Gear - Fade from Red to Green
        if (ledGear == 1) {
            redValue -= 1;
            greenValue += 1;
        }
        //Second Gear - Fade from Green to Blue
        if (ledGear == 2){
            greenValue -= 1;
            blueValue += 1;
        }
        //Third Gear - Fade from Blue to Red
        if (ledGear == 3){
            blueValue -= 1;
            redValue +=1;
        }
        //Gear Switching
        if (greenValue == maxBright) ledGear = 2;
        if (blueValue == maxBright) ledGear = 3;
        if (redValue == maxBright+1) ledGear = 4;
        delay(shortDelay); 
    } while (ledGear < 4);
    delay(longDelay);
}
