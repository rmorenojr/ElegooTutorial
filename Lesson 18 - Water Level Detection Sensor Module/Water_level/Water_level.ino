/* ***********************************************************
 *  Water Level 
 *     Uses the Water Level Detection Sensor Module
 *     Modified by Ricardo Moreno
 *     July 11, 2018
 *
 *  Original sketch by:
 *     www.elegoo.com
 *     2016.12.9
 */

/* ***********************************************************
 *                      Global Constants                     *
 * ********************************************************* */
const int sensorPin = A0;                        // using alias for analog pin 0
                                                 // analog alias A0-A5 input pins = D14-D19
bool tapWater = true;                            // Boolean if using plain tap water

/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
int HistoryValue = 0;
//char printBuffer[20];                            // Make sure to adjust array value if you change the string
//char printBuffer[30];                            // Make sure to adjust array value if you change the string
char printBuffer[45];                            // Make sure to adjust array value if you change the string
String analogPin;

/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup()
{
  Serial.begin(9600);
  analogPin = analogPinConverter(sensorPin);
}

int levelConverter(int sensorValue, bool isCleanWater = true){
  int percentage;
  static int maxValue = 350;

  if (isCleanWater){
    percentage = map(sensorValue, 0, maxValue, 0, 100);
    if (percentage > 100) { 
      maxValue = sensorValue; 
      percentage = 100;
    }
  }else{
    percentage = map(sensorValue, 0, 1023, 0, 100);
  }
  return percentage;
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop()
{
  int currentValue = analogRead(sensorPin);    // get sensorPin analog value
  int diffValue = HistoryValue - currentValue;
  if((abs(diffValue) >= 10)||((currentValue == 0)&&(HistoryValue != 0)))
  {
    int percentValue = levelConverter(currentValue, tapWater);
    //[original]  sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
    // sprintf(printBuffer,"PIN %03d level is %04d\n", sensorPin, currentValue); 
    // sprintf(printBuffer,"PIN %s level is %04d)\n", analogPin.c_str(), currentValue);
    sprintf(printBuffer,"PIN %s level is %03d%% (raw value is %04d)\n", analogPin.c_str(), percentValue, currentValue);
    Serial.print(printBuffer);
    HistoryValue = currentValue;
  }
}

String analogPinConverter(int value){
  String analogPinValue; 

  switch(value){
    case 14:                                  // D14 = A0
      analogPinValue = "A0";
      break;
    case 15:                                  // D15 = A1
      analogPinValue = "A1";
      break;
    case 16:                                  // D16 = A2
      analogPinValue = "A2";
      break;
    case 17:                                  // D17 = A3
      analogPinValue = "A3";
      break;
    case 18:                                  // D18 = A4
      analogPinValue = "A4";
      break;
    case 19:                                  // D19 = A5
      analogPinValue = "A5";
      break;
    default:
      analogPinValue = "Pin Error"; 
      break;
  }
  return analogPinValue;   
}

