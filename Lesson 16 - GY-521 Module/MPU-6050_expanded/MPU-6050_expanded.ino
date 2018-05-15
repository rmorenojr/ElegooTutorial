/* ***********************************************************
 *  MPU-6050 expanded tutorial sketch - v1.0
 *    Uses the Wire.h library
 *         the GY-521 Module
 *         The Arduino UNO R3
 *    Modified by Ricardo Moreno
 *    May 08, 2018
 *
 *  Inspired by Elegoo Lesson 16 and EEEthusiast
 *    Ep. 57 Arduino Accelerometer & Gyroscope Tutorial MPU-6050 6DOF Module
 *    Website: http://eeenthusiast.com/
 *    video: https://www.youtube.com/watch?v=M9lZ5Qy5S2s&t=0
 *    Sketch: https://github.com/VRomanov89/EEEnthusiast/tree/master/MPU-6050%20Implementation/MPU6050_Implementation
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
 *  05/08/2018 V1.0 - Initial release
 */

/* ***********************************************************
 *                          Library                          *
 * ********************************************************* */
#include <Wire.h>

/* ***********************************************************
 *                      Global Constants                     *
 * ********************************************************* */
const int MPU_addr=0x68;               // I2C address of MPU-6050
  /* I2C address can be found in the datasheet Section 9.2 I2C Interface
     Depending if AD0 is set to HIGH or LOW results in different address:
        PIN        Binary    Hex    Dec
     | AD0 HIGH | b1101001 | 0x69 | 105 |
     | AD0 LOW  | b1101000 | 0x68 | 104 |
  */

/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
// unsigned long = 32 bits
// unsigned int = 16 bits
int16_t AcX, AcY, AcZ;                 //accelerometer - force it to be a 16-bit integer
float gForceX, gForceY, gForceZ;
int AcRange = 0;                       //accelerometer Range at the cost of Sensitivity - see setupMPU
                                       //values 0, 1, 2, 3

int16_t GyX, GyY, GyZ;                 //gyroscope - force it to be a 16-bit integer
float rotX, rotY, rotZ;
int GyRange = 0;                       //gyroscope Range at the cost of Sensitivity - see setupMPU
                                       //values 0, 1, 2, 3

float Tmp;                             //temperature

int loopDelay = 333;

/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop() {
  recordAccel();
  recordTemperature();
  recordGyro();
  printData();
  delay(loopDelay);
}

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */

void setupMPU(){
  /* *********************************************************
     This function consists of three parts:
       Sets the MPU-6050 Power Management Device reset, sleep mode,
         cycle mode, and Temperature disable bits to zero
       Sets Accelerometer sensitivity
       Sets Gyroscope Sensitivity
     Could be called again if a change in sensitivty is desired
  */

  //Local Variable
  byte c;                              //byte should be a unsigned 8-bit value
  byte buffer[1];

  /* *********************
   *       PWR_MGMT_1    *
   ********************* */
  /* Power Management Section 4.28 in Register Map Datasheet.  Since the MPU-6050
     powers up in sleep mode, we'll need to wake it.
      Register  Bit7     Bit6   Bit5   Bit4   Bit3   Bit2  Bit1  Bit0
     |   6B   |Device | Sleep | Cycle |  -  | Temp  |    CLKSEL       |
     |        | Reset |       |       |     |Disable|  (clock source) |       
     -->Page 9 (in section 4) see Note: The device will come up in sleep mode upon power-up. 
  */
  readFrom(0x6B,1,buffer);
  c = buffer[1] & 0x07;                //Registry Value AND with 0b00000111 zeros bits 7,6,5,4 & 3  
  writeTo(0x6B,c);                     //Then we set the bits to zero and keep the clock source bits the same
  //OR writeTo(0x6B,0);
  //Caution: this will also set the clock source to zero - which in this case is ok
  //  if you didn't want to change the clock source (example using an external clock)
  //  use a method like above. 
  
  /* *********************
   *      GYRO_CONFIG    *
   ********************* */
  /* Gyroscope Configuration Section 4.4 in Register Map Datasheet
     full scale range: ±250, ±500, ±1000, ±2000°/sec
      Register  Bit7    Bit6    Bit5     Bit4   Bit3    Bit2  Bit1  Bit0
     |   1B   | XG_ST | YG_ST | ZG_ST |Full Scale Range|  -  |  -  |  -  |
     |        |       |       |       | Select FS_SEL  |     |     |     |
     (Setting XG_ST,TG_ST and ZG_ST to 1 will perform a self test)

     Section 4.19 Gyroscope Measurements: 
      FS_SEL    Binary    Full Scale Range 
     |   0   |      0  |     ±250°/sec     |
     |   1   |   1000  |     ±500°/sec     |
     |   2   |  10000  |    ±1000°/sec     |
     |   3   |  11000  |    ±2000°/sec     |
     -->Note: FS_SEL/360*60sec/min = RotationValue in RPM
        Sensitivity decreases with larger range.
  */
  switch (GyRange){                    //GyRange set in Global Variables above
     case 0:
       writeTo(0x1B,0x0);              //Set GYRO_CONFIG to FS_SEL ±250°/sec
       break;
     case 1:
       writeTo(0x1B,0x8);              //Set GYRO_CONFIG to FS_SEL ±500°/sec
       break;
     case 2:
       writeTo(0x1B,0x10);             //Set GYRO_CONFIG to FS_SEL ±1000°/sec
       break;
     case 3:
       writeTo(0x1B,0x18);             //Set GYRO_CONFIG to FS_SEL ±2000°/sec
       break;
     default:
       writeTo(0x1B,0x0);              //Set GYRO_CONFIG to FS_SEL ±250°/sec
  }

  /* *********************
   *     ACCEL_CONFIG    *
   ********************* */
  /* Accelerometer Configuration Section 4.5 in the Register Map datasheet
     full scale range: ±2g, ±4g, ±8g, and ±16g
     Register   Bit7    Bit6    Bit5     Bit4   Bit3    Bit2  Bit1  Bit0
     |   1C   | XA_ST | YA_ST | ZA_ST |Full Scale Range|  -  |  -  |  -  |
     |        |       |       |       | Select AFS_SEL |     |     |     |
     (Setting XA_ST,TA_ST and ZA_ST to 1 will perform a self test) 

     Section 4.17
      AFS_SEL   Binary  Full Scale Range 
     |   0   |      0  |     ±2g        |
     |   1   |   1000  |     ±4g        |
     |   2   |  10000  |     ±8g        |
     |   3   |  11000  |    ±16g        |
  */   
  switch (AcRange) {                   //AcSensitivity set in Global Variables above
     case 0:
       writeTo(0x1C,0x0);              //Set ACCEL_CONFIG to AFS_SEL ±2g
       break;
     case 1:
       writeTo(0x1C,0x8);              //Set GYRO_CONFIG to AFS_SEL ±4g
       break;
     case 2:
       writeTo(0x1C,0x10);             //Set GYRO_CONFIG to AFS_SEL ±8g
       break;
     case 3:
       writeTo(0x1C,0x18);             //Set GYRO_CONFIG to AFS_SEL ±16g
       break;
     default:
       writeTo(0x1C,0x0);              //Set GYRO_CONFIG to AFS_SEL ±2g
  }
}

void writeTo(byte toAddress, byte value) {
  /* ********************************************************* 
    Generic Wire.write() registry byte routine
         toAddress - registry location value
             value - numeric byte value
  */  
  Wire.beginTransmission(MPU_addr);    // This begins the I2C communication to the MPU 
  Wire.write(toAddress);               // Access the register
  Wire.write(value);                   // Set the byte value to register above
  Wire.endTransmission(true);          // Close I2C communication
}

void readFrom(byte fromAddress, int num, byte results[]){
  /* ********************************************************* 
     Generic Wire.read() registry byte routine
       fromAddress - registry location value
               num - number of bytes
         results[] - array to store byte values
  */
  Wire.beginTransmission(MPU_addr);    //I2C address of the MPU
  Wire.write(fromAddress);             //Starting register for Readings
  Wire.endTransmission(false);         //This resent the request and holds the MPU for exclusive communication
  Wire.requestFrom(MPU_addr,num,true); //Request num Registers bytes and releases I2C
  int i = 0;
  while(Wire.available()) {
    results[i] = Wire.read();          //Stores values in buffer arrray
    i++;
  }
}

void recordAccel() {
  /* ********************************************************* 
      Section 4.17 Accelerometer Measurements Registers 3B - 40
      Note the values are broken up into High and Low bytes so we
      must store the first value and shift it 8 bits over and OR it
      with the second value to form the 16 bit value.
  */
  //Local Variable
  byte buffer[6];

  readFrom(0x3B,6,buffer);
  AcX = buffer[0]<<8|buffer[1];        //Store two bytes 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  //AcX = buffer[0]*256+buffer[1];     // OR you could also do this
  AcY = buffer[3]<<8|buffer[4];        //Store two bytes 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = buffer[5]<<8|buffer[6];        //Store two bytes 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  processAccelData();
}

void processAccelData(){
  /* ********************************************************* 
     Section 4.17 Accelerometer Measurements  

      AFS_SEL Binary Full Scale Range  LSB Sensitity
     |   0   |   0  |     ±2g        |  16384 LSB/g |
     |   1   |   1  |     ±4g        |   8192 LSB/g |
     |   2   |  10  |     ±8g        |   4096 LSB/g |
     |   3   |  11  |    ±16g        |   2048 LSB/g |

     --> g force in direction = AcX/LSB Sensitivity
  */   
  //Local Variable
  float LSB;

  switch (AcRange){
     case 0:
       LSB = 16384.0;                  //AFS_SEL ±2g
       break;
     case 1:
       LSB = 8192.0;                   //AFS_SEL ±4g
       break;
     case 2:
       LSB = 4096.0;                   //AFS_SEL ±8g
       break;
     case 3:
       LSB = 2048.0;                   //AFS_SEL ±16g
       break;
     default:
       LSB = 16384.0;                  //AFS_SEL ±2g
  }
  gForceX = (float)(AcX) / LSB;
  gForceY = (float)(AcY) / LSB; 
  gForceZ = (float)(AcZ) / LSB;
}

void recordTemperature() {
  /* ********************************************************* 
     Section 4.18 Temperature Measurement
     The scale factor and offset for the temperature sensor are found
     in the Electrical Specifications table (Section 6.3 of the 
     MPU-6000/MPU-6050 Product Specification document).
       Range = -40 to +85
       Sensitivity = 340
       Temperature offset = -521 at 35°C            = B1111110111110111
         therfore:
           C = (RawData - offest)/340 = RawData/340 - offset/340
           offset = -521-(340*35) = -12412
           C = RawData/340 - (-12412)/340 = RawData/340 + 36.51  (that's funny, equation provided shows 36.53)
     Note: the measurement is stored as a signed 16-bit number
  */
  //Local Variable
  byte buffer[2];
  int rTmp;                            //Raw temperature Temperature number signed integer

  readFrom(0x41,2,buffer);
  rTmp=buffer[0]<<8|buffer[1];         //Stores two bytes 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp = (float)rTmp/340.00 + 36.53;    //equation for temperature in degrees C from datasheet
}

void recordGyro() {
  /* ********************************************************* 
      Section 4.19 Gyroscope Measurements  Registers 0x43 - 0x48
      Note the values are broken up into High and Low bytes so we
      must store the first value and shift it 8 bits over and OR it
      with the second value to form the 16 bit value.
  */   
  //Local Variable
  byte buffer[6];

  readFrom(0x43,6,buffer);             //Request Gyro Registers (43 - 48)
  GyX = buffer[0]<<8|buffer[3];        //Store two bytes 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = buffer[3]<<8|buffer[4];        //Store two bytes 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = buffer[5]<<8|buffer[6];        //Store two bytes 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  processGyroData();
}

void processGyroData() {
  /* ********************************************************* 
     Section 4.19 Gyroscope Measurements: 
      FS_SEL Binary Full Scale Range  LSB Sensitity
     |   0   |   0  |     ±250°/s    | 131.0 LSB/°/s |
     |   1   |   1  |     ±500°/s    |  65.5 LSB/°/s |
     |   2   |  10  |    ±1000°/s    |  32.8 LSB/°/s |
     |   3   |  11  |    ±2000°/s    |  16.4 LSB/°/s |

     --> rotation force in direction = GyX/LSB Sensitivity
     Note that the measurement stored is a 16-bit 2's complement value
  */
  //Local Variable
  float LSB;

  switch (GyRange){
     case 0:
       LSB = 131.0;                    //FS_SEL ±250°/s
       break;
     case 1:
       LSB = 65.5;                     //FS_SEL ±500°/s
       break;
     case 2:
       LSB = 32.8;                     //FS_SEL ±1000°/s
       break;
     case 3:
       LSB = 16.4;                     //FS_SEL ±2000°/s
       break;
     default:
       LSB = 131.0;                    //FS_SEL ±250°/s
  }
  rotX = (float)(GyX) / LSB;
  rotY = (float)(GyY) / LSB; 
  rotZ = (float)(GyZ) / LSB;
}

void printData() {
  /* ********************************************************* 
     Print the output to the serial monitor
  */
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print("\t");    // prints a tab
  Serial.print("Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.print(gForceZ);
  Serial.print("\t");    // prints a tab
  Serial.print(" Temp=");
  Serial.println(Tmp);
}

