/*Ultrasonic Distance - using the HC-SR04 Ultrasonic Sensor Module
 *  By Ricardo Moreno
 *  02/13/208
 *
 * Using the Ultrasonic Sensor without a Library
 *
 * Inspired by:
 * LESSON 17: Measure Speed of Sound with Arduino and Ultrasonic Sensor
 * https://www.youtube.com/watch?v=eaHRHQ5Ca_U
 *
 * Lesson 18: Measure Distance with Arduino and Ultrasonic Sensor by Paul McWhorter
 * https://www.youtube.com/watch?v=rTM5gZxBPmY
 *
 * Speed of sound
 *  changes with with temperature
 *  at 68 degrees F (20 degrees C)
 *    741 Miles per hour
 *    1087 feet per sec
 *    343.2 meters per second
 *    776.5 Miles per Hour (Mph) @ 77 degrees F - Paul McWhorter
 *    345.2944 meters per second @ 73 degrees F
 * Formula for speed of sound with temperature change:
 *  sos = 331.5*sqrt(1+C/273.15)  - in meters per second - C is degrees C
 */

// HC-SR04 module pins
const int triggerPin = 12;
const int echoPin = 11;

//Global Variables
//float speedOfSound = 343.2;              //Meters per second @ 20C or 68F
float speedOfSound = 343.2611;             //Meters per second @ 67F
float conversionFactor = .0001;            //conversion factor for meters to cm & uSec to Sec
unsigned int pingTime = 0;                 //The time single round trip time - avail after call to distance
unsigned int pingTimeAvg = 0;              //The average round trip time - avail after call to distanceAvg

/* *******************************************************
 *                         Setup
 ********************************************************* */
void setup() {
   pinMode(triggerPin,OUTPUT);
   pinMode(echoPin,INPUT);
   Serial.begin(9600);                     //Enable the Serial Monitor
   delay(1000);
}

/* *******************************************************
 *                       Functions
 ********************************************************* */
float distance(){
  /* distance returns a float value in centimeters
   *  Parameters: none
   */
  float dist = 0.0;
  
  digitalWrite(triggerPin, LOW);           //Set the trigger pin low
  delayMicroseconds(5);                    //pause to let signal settle
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(12);                   //pause HIGH state
  digitalWrite(triggerPin, LOW);           //Bring trigger down low
  //Change the global variable pingtime
  pingTime = pulseIn(echoPin, HIGH, 18000);//Measure ping time at echo pin in microseconds
                                           //timeout time in microseconds max about 3 meters
  //distance = speed of sound (meters per second) * 1000cm/meter * ping time/2 (uSeconds) * 1sec/1000000uSec
  dist = speedOfSound * conversionFactor * pingTime/2;  //convert the target distance to cm
  return dist;
}

float distanceAvg(unsigned int wait=1, unsigned int pings=5, unsigned int trimPercent=0){
  /* distanceAvg returns a float value in centimeters
   *   Parameters:    
   *   [optional]wait        - the time between distance checks in milliseconds, 
   *                           default value is 1    
   *   [optional]pings       - the number of distance checks, default value is 5
   *   [optional]trimPercent - this is kinda like EXCEL's TRIMMEAN function
   *                           Based upon the trim percentage passed, it 
   *                           determines the trim count from minimum and
   *                           maximum values: 
   *                             trimCount = rounddown(pings*(trimPercent/100)/2) 
   *                           default value is zero which doesn't trim outlying points
   */
  float minVal = 0.0;
  unsigned long minTime = 0;
  float maxVal = 0.0;
  unsigned long maxTime = 0;
  float d[pings];
  float t[pings];
  float avgDist = 0.0;
  unsigned long avgTime = 0;
  unsigned int count = pings;
  unsigned int trimCount = 0;
    
  //Parameter checking
  if (count < 1) count = 1;
  if (wait < 1) wait = 1;                  //time in milliseconds
  if (trimPercent < 0) trimPercent = 0;
  if (trimPercent > 100) trimPercent = 100;
   
  if (trimPercent == 0){
    trimCount = 0;
  } else {
    trimCount = int(count*(trimPercent/100.)/2.);  //always round down to nearest integer
    if (trimCount == 0) trimCount=1;
  }
  
  //Get all the raw data
  for (int x = 0; x < count; x++) {
    d[x] = distance();
    if ((minVal > d[x])||(minVal == 0)) minVal=d[x];
    if ((maxVal < d[x])||(maxVal == 0)) maxVal=d[x];
    t[x] = pingTime;
    if ((minTime > pingTime)||(minTime == 0)) minTime = pingTime;
    if ((maxTime < pingTime)||(maxTime == 0)) maxTime = pingTime;
    avgDist += d[x];
    avgTime += pingTime;
    delay(wait);
  }

  //No need to sort if trimCount = 0 or 1
  if ((count > 1)&&(trimCount > 1)){
    //Insert sort routine
    //http://forum.arduino.cc/index.php?topic=49059.0
    //Sort distances
    for (int i = 1; i < count; ++i){
      float temp = d[i];
      int k;
      for (k = i - 1; (k >= 0) && (temp < d[k]); k--){
        d[k + 1] = d[k];
      }
      d[k + 1] = temp;
    }
    //sort ping times
    for (int i = 1; i < count; ++i){
      float temp = t[i];
      int k;
      for (k = i - 1; (k >= 0) && (temp < t[k]); k--){
        t[k + 1] = t[k];
      }
      t[k + 1] = temp;
    }
  }
   
  if (trimCount == 1){                     // substract highest and lowest values
    avgDist -= (maxVal + minVal);
    avgTime -= (maxTime + minTime);
    count -= 2;
  }else if (trimCount > 1){                //subtract the highest and lowest points
    //subtract the lowest data points
    for (int i = 0; i < trimCount; i++) {
      avgDist -= d[i];
      avgTime -= t[i];
    }
    //subtract the highest data points
    for (int i = count-1; i > (count-1-trimCount); i--){
      avgDist -= d[i];
      avgTime -= t[i];
    }
    count -= trimCount*2;                  //revise count less the upper and lower trimcounts
  }                                        //Else assume trimCount == 0
  // calculate average
  avgDist /= count;
  avgTime /= count;
  pingTimeAvg = avgTime;                   //Set global value pingTimeAvg
  return avgDist;
}

/* *******************************************************
 *                      Void Loop
 ********************************************************* */
void loop(){
   unsigned int timeValue;                    //The system time

   float answer = distance();
   Serial.println("Single shot functions");
   Serial.print("  Distance = ");
   Serial.print(answer);                      //in centimeters
   Serial.println(" cm");
   answer /= 2.54;
   Serial.print("  Distance = ");
   Serial.print(answer);                      //in inches
   Serial.println(" inches");

   Serial.print("  Single round trip time ");
   Serial.print(pingTime);
   Serial.println(" uSeconds");
   Serial.println("");
   delay(25);
   //Find a distance average with a trim mean of 20 percent
   timeValue = millis();
   answer = distanceAvg(2, 20, 20);
   timeValue = millis() - timeValue;
   Serial.println("Average functions:");
   Serial.print("  Distance = ");
   Serial.print(answer);
   Serial.println(" cm");
   answer /= 2.54;
   Serial.print("  Distance = ");
   Serial.print(answer);                       //in inches
   Serial.println(" inches");
   Serial.print("  Average round trip time is ");
   Serial.println(pingTimeAvg);
   Serial.println("");
   Serial.print("It took ");
   Serial.print(timeValue);
   Serial.println(" milliseconds to complete");
   Serial.println("function distance average");   
   Serial.println("");
   delay(2000);
}

