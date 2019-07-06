/* ********************************************************************** 
 * DC_Motor
 *   Uses: one DC Motor
 *         one L293D Quadruple half H-Bridge driver IC
 *         one Breadboard Power Supply, MB-102
 *   
 * Inspired by Elegoo Lesson 29 
 *   www.elegoo.com     2016.12.12
 *   modified by Ricardo Moreno
 *
 * Description:
 *   This sketch illustrates controlling a DC Motor using an
 *   L293D Quadruple half H-Bridge driver IC.  Note that the "D" 
 *   indicates inductive transient suppression diodes are 
 *   integrated in the IC. It's recommended that a separate
 *   power supply is is used.
 *   
 * Circuit:             L293D
 *                     _______
 *    Arduino 5---EN12-|     |-VCC1---5V
 *    Ardunio 4-----1A-|     |-4A
 *     DCMotor+-----1Y-|     |-4Y
 *          GND--------|     |--------GND
 *          GND--------|     |--------GND
 *     DCMotor- ----2Y-|     |-3Y     
 *    Arduino 3-----2A-|     |-3A
 *      4.5-36V---VCC2-|     |-EN34
 *                     -------
 * History:
 *  6/16/2019 v1.0 - Initial release
 *  7/01/2019 v1.1 - Additional comments, minor rev to void loop
 *                   
 ********************************************************************* */

/* ***************************************************
 *                Global Constants                   *
 *************************************************** */
const int Enable12 = 5;  // PWM pin to L293D's EN12 (pin 1) 
const int Driver1A = 4;  // To L293D's 1A (pin 2)
const int Driver2A = 3;  // To L293D's 2A (pin 7)

/* ***************************************************
 *                Global Variables                   *
 *************************************************** */
//none

/* ***************************************************
 *           Global Adjustable Variables             *
 *************************************************** */
//none

/* ***************************************************
 *                   Void Setup                      *
 *************************************************** */ 
void setup(){
    //---set pin direction
    pinMode(Enable12,OUTPUT);
    pinMode(Driver1A,OUTPUT);
    pinMode(Driver2A,OUTPUT);
    Serial.begin(9600);
}

/* ***************************************************
 *                   Functions                       *
 *************************************************** */    
void motorCTRL(byte speed, bool D1A, bool D2A){
    /*  motorCTRL controls the DC motor
     *    speed: any value between 0-255, used as PWM
     *             0 - off
     *           255 - maximum
     *      D1A: Input 1 or 1A, boolean value of HIGH or LOW          
     *      D2A: Input 2 or 2A, boolean value of HIGH or LOW
     */
	analogWrite(Enable12,speed);  // PWM
	digitalWrite(Driver1A,D1A);   // Boolean
	digitalWrite(Driver2A,D2A);   // Boolean 
}

/* ***************************************************
 *                   Void Loop                       *
 *************************************************** */
void loop() {
	Serial.println("One way, then reverse");
    //---back and forth example
	for (int i=0;i<5;i++){
        motorCTRL(255,HIGH,LOW);  // one way
		delay(500);
		motorCTRL(255,LOW,HIGH);  // reverse
		delay(500);
	}
	motorCTRL(0,LOW,HIGH);        // Stop
	delay(2000);

	Serial.println("fast Slow example");
	//---fast/slow stop example
	motorCTRL(255,HIGH,LOW);      // one way
	delay(3000);
	motorCTRL(0,HIGH,LOW);        // slow stop
	delay(2000);
	motorCTRL(255,LOW,HIGH);      // reverse
	delay(3000);
	motorCTRL(255,LOW,LOW);       // fast stop
	delay(2000);

	Serial.println("PWM full then slow");
	//---PWM example, full speed then slow
	for(int x = 255; x >= 55; x -= 25){
        motorCTRL(x,HIGH,LOW);
        delay(1000);
    }
	motorCTRL(0,HIGH,LOW);        // Stop
    delay(2000);

	Serial.println("PWM slow then full");
	//---PWM example, slow then full speed
    for(int x = 55; x <= 255; x += 25){
        motorCTRL(x,HIGH,LOW);
        delay(1000);
    }
	motorCTRL(0,HIGH,LOW);        // Stop
	delay(10000);
}
   
