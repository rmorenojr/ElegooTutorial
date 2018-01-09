
/* The Most Complete Starter Kit by Elegoo
 *  For the Arduino UNO R3
 *  LESSON 4 - RGB LED
 *  
 *  Original by - HowToMechatronics.com and Elegoo.com
 *  Modified by - Ricardo Moreno
 *  Date 1/5/2018
 */

//The Arduino Web site recommends that one uses const rather than #define since
//using #define could have unwanted side effects

// Global Variables
const int redPin = 6;    // Red LED pin
const int greenPin = 5;  //Green LED pin
const int bluePin = 3;   //Blue LED pin
int maxBright = 255;  //Maximum LED brightness

void setup(){
  Serial.begin(9600);  //Turn On the Serial Port
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

// main loop
void loop(){
  //Local Variable
  int delayTime = 1000; // fading time between colors
  int shortDelay = 10;  // short time delay between colors
  int redValue;
  int greenValue;
  int blueValue;
  int ledGear;  // For switching LED fading 

  //I combined various ways to turn on the RGB LED
  //Here we manually set the color
  Serial.println("Manual Colors");
  setColor(maxBright, 0, 0);  //Red Color
  delay(delayTime);
  setColor(0, maxBright, 0);  //Green Color
  delay(delayTime);
  setColor(maxBright, maxBright, maxBright);  //White Color
  delay(delayTime);
  setColor(170, 0, maxBright);  //Purple Color
  delay(delayTime);

  Serial.println("Fade from Red to Green");
  //Fade from Red to Green
  delay(delayTime);
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
  delay(delayTime);
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
  delay(delayTime);
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
  delay(delayTime);
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
  delay(delayTime);
}

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



