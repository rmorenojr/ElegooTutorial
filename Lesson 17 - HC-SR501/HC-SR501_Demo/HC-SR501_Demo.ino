/* ***********************************************************
 *  HC-SR501 Motion Sensor Demonstration
 *     Uses the HC-SR501 PIR Sensor
 *     Modified by Ricardo Moreno
 *     June 23, 2018
 *
 *  Inspired by Elegoo Lesson 17 and DroneBot
 *     Motion Sensor with Delay
 *     DroneBot Workshop 2018
 *     https://dronebotworkshop.com
 *
 *  Note: Set the sensor for 3-second trigger
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *  
 *  History:
 *  06/23/2018 V1.0 - Initial release
 */

/* ***********************************************************
 *                      Global Constants                     *
 * ********************************************************* */
// Set the Arduino pins
const int detectedLED = 10;              // Blue LED Pin
const int readyLED = 9;                  // Green LED Pin
const int waitLED = 8;                   // Red LED Pin
const int pirPin = 7;                    // Input from Motion Sensor
const int BuzzerPin = 11;                // Active buzzer pin

//Set Detection Constants for Different States
const int TRIGGERED = 2;
const int READY = 1;
const int WAIT = 0;

//Set Constant DELAY or ON times here
const int BuzzerOnTime = 500;            // Active Buzzer time
const int dotLength = 40;                // Number of progress dots max per row
const unsigned int initialDelay = 60000; // Initial startup delay
const unsigned int divisor = 40000;      // Period of time between progress periods
/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
bool BuzzerOnState = false;              // Buzzer State
int pirValue;                            // PIR Output value
int pirState;                            // Stores the PIR State
unsigned long triggeredStartTime;        // Stores Start time
unsigned long waitStartTime;             // Stores Wait Start time - 
                                         //   when output pin switches from High to Low
unsigned int timeDelay;                  // Time delay - 
                                         //   manually adjust time delay to 3 seconds
                                         //   software recorded
unsigned int waitDelay = 7000;           // Wait delay is after time delay - 
                                         //   software adjusted

/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup(){
  Serial.begin(9600);
  
  /*                     Setup PinModes                      */
  // LEDs as Outputs  
  pinMode(detectedLED, OUTPUT);
  pinMode(readyLED, OUTPUT);
  pinMode(waitLED, OUTPUT);
  // Buzzer as Outputs
  pinMode(BuzzerPin, OUTPUT);
  // PIR as Input
  pinMode(pirPin, INPUT);

  /*      Initial 1 Minute Delay to stabilize sensor        */
  Serial.println("Wait one minute to stabilize sensor");
  showLEDs(WAIT);

  // Make progress trailing dots
  for (int i=0; i<= initialDelay/400; i++){
    //This loop makes the trailing dots across the screen.
    if ((i%(dotLength-5)==0)&&(i>0)&&(i==(dotLength-5))){
      //First Line
      Serial.println(".");
    } else if (((i-(dotLength-5))%dotLength==0)&&(i>(dotLength-4))){
      //Lines after
      Serial.println(".");
    } else {
      Serial.print(".");
    }
    delay(400);
  }
  showLEDs(READY);
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop(){
  static int i;
  switch (pirState){
    case READY:
        pirValue = digitalRead(pirPin);
        if (pirValue) {
          pirTriggered();
          i=0;
        }
        break;
    case TRIGGERED:
        /* NOTE: While triggered, PIR output will remain high until
           time delay is passed. If repeatable trigger mode is
           enabled, it will reset the time delay.
           
           At this point, the Arduino cannot do anything but monitor
           the output 
        */
        // Make progress trailing dots
        if (i%divisor==0) {Serial.print(".");}
        
        //Check for Low PIR value
        pirValue = digitalRead(pirPin);
        if (!pirValue) {                                 //times up
          /*  Wait time begins */
          waitStartTime = millis();
          timeDelay = waitStartTime-triggeredStartTime;  // Records the actual time delay
          Serial.print("timeDelay = "); Serial.print(timeDelay); Serial.println("ms");
          showLEDs(WAIT);
          i=0;
        }

        //Check Buzzer
        if ((BuzzerOnState)&&((millis()-triggeredStartTime)>= BuzzerOnTime)){
          BuzzerOnState = false;
          digitalWrite(BuzzerPin, LOW);
        }
        i++;
        break;
    case WAIT:
        // Make progress trailing dots
        if (i%divisor==0) {Serial.print(".");}

        // Check time > waitDelay 
        if ((millis()-waitStartTime)>= waitDelay) {
          Serial.print("waitDelay = "); Serial.print(waitDelay); Serial.println("ms");
          showLEDs(READY);
          i=0;
        }

        /* NOTE: Since PIR hardware is not controlled by the Arduino, 
           wait delay is approximate. If early motion detection is 
           discovered, quickly record the new value and switch states
        */
        pirValue = digitalRead(pirPin);
        if (pirValue) {
          // Autocorrection Routine:
          // record new wait delay and jump to Triggered State
          waitDelay = millis()-waitStartTime;
          Serial.println("PreTriggered!");
          Serial.print("Autocorrecting waitDelay = "); Serial.print(waitDelay); Serial.println("ms");
          pirTriggered();                                //Turn on Triggered LED and switch to Triggered State
          i=0;
        }
        i++;
        break;
    default:
        // do nothing
        break;
  }
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */
void pirTriggered(){
  /*   This Subroutine switches on all the things that need
   *   to happen during a triggered event.
   */
  triggeredStartTime = millis();         // Record Triggered Start Time
  showLEDs(TRIGGERED);                   // Show Triggered LED
  digitalWrite(BuzzerPin, HIGH);         // Enable Buzzer
  BuzzerOnState = true;                  // Enable Buzzer State 
  Serial.print("Measuring Delay.");
}

void showLEDs(int value){
  pirState = value;
  switch (value){
    case WAIT:                           //WAIT
        Serial.print("Wait");            // to be followed by progress dots
        digitalWrite(detectedLED, LOW);
        digitalWrite(readyLED, LOW);
        digitalWrite(waitLED, HIGH);
        break;
    case READY:                          //READY
        Serial.println("Ready");
        digitalWrite(detectedLED, LOW);
        digitalWrite(readyLED, HIGH);
        digitalWrite(waitLED, LOW);
        break;
    case TRIGGERED:                      //TRIGGERED
        Serial.println("Triggered!");
        digitalWrite(detectedLED, HIGH);
        digitalWrite(readyLED, LOW);
        digitalWrite(waitLED, LOW);
        break;
    default:
        // Maybe add error code here
        // do nothing
        break;
  }
}

