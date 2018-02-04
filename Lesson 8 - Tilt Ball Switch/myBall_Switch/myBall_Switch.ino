//www.elegoo.com
//2016.12.08
/*****************************************/
//Using predefined LED_BUILTIN = 13
const int tiltSensorPin = 2;             //the tilt bal switch pin

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);         //initialize the ledPin as an output
  pinMode(tiltSensorPin,INPUT_PULLUP);  //set the tilt switch input and set to high using pull up resistors
 
} 

/******************************************/
void loop() 
{  
  int digitalVal = digitalRead(tiltSensorPin);           //Returns a HIGH or LOW
  if(digitalVal)
  {
    digitalWrite(LED_BUILTIN, LOW);                      //turns the led off
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);                     //turns the led on 
  }
}
/**********************************************/

