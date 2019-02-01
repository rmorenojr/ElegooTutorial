/* ***********************************************************
 * RFID_module sketch - v1.0
 *   Uses the RFC522 RFID Module and tags
 *   Uses the SPI.h library
 *   Uses the MFRC522.h library
 *
 * Inspired by Elegoo Lesson 21, and by Dejan Nedelkovski
 *   www.HowToMechatronics.com
 *   Arduino Door Lock Access Control Project
 *   https://howtomechatronics.com/tutorials/arduino/rfid-works-make-arduino-based-rfid-door-lock/
 *
 * Description:
 *   This sketch illustrates some of the functionality of the 
 *   RFC522 RFID module and tags. Set the card tag as a Master
 *   and use it to authorize the keychain tag. 
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
 *  01/20/2019 v1.0 - Initial release
 *
 * @author Ricardo Moreno
 ********************************************************** */ 

/* ***********************************************************
 *                         Libraries                         *
 * ********************************************************* */
#include <SPI.h>
#include <MFRC522.h>

/* ***********************************************************
 *                      Global Constants                     *
 *                    Hardware Definitions                   *
 * ********************************************************* */
 /* Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
   // Other hardware pins
    const byte rstPin =  9;                // Reset pin
    const byte  ssPin = 10;                // Slave Select pin
    
    // Instantiate MFRC522 object class
    MFRC522 rfidReader(ssPin, rstPin);
 
    // Other Global Constants 
    const long timeout = 30000;            // Timeout in ms 
    
/* ***********************************************************
 *                      Global Variables                     *
 * ********************************************************* */
    char* myTags[100] = {};
    int tagsCount = 0;
    String tagID = "";

bool readRFID(long _timeout=timeout, bool useTimeout=false){
    /*  readRFID will continuously check the RFID reader for the presence of
     *    a tag from and will attempt to get tag IDs. Updates global value
     *    tagID via getTagID function.
     *  Parameters:
     *    _timeout   - [optional] the length of time before functio gives up
     *                 default value = global timout value
     *    useTimeout - [optional] boolean to enforce timout period or wait 
     *                 indefinately.  Default value = false.
     *  Returns:
     *    true  -  successfully reads tag ID
     *    false -  unsuccessful in reading the tag ID          
     */
    bool successRead = false;

    unsigned long startTime = millis();
    unsigned long currentTime = startTime;
    // S'U'+S'T'
    // T  = (currentTime-startTime) > timeout
    // T' = (currentTime-startTime) < timeout
    while (((successRead==false)&&(useTimeout==false)) || ((successRead==false)&&((currentTime - startTime) < _timeout))) {    
        if (isTagPresent() == true){ successRead = getTagID(); }
        currentTime = millis();
    }
    return successRead;
}

/* ***********************************************************
 *                         Void Setup                        *
 * ********************************************************* */
void setup() {
    // Initiating
    Serial.begin(9600);                     // Start the serial monitor
    SPI.begin();                            // Start SPI bus
    rfidReader.PCD_Init();                  // Start MFRC522 object

    while (!Serial);                        // Do nothing if no serial port is opened
    
    // Obviously this is an over simplified sketch
    // Master tags would be save in flash storage and
    // retrieved here.  OR a special PIN entered to set
    // Master Tag.
    // But for the sake of simplicity, the sketch will 
    // obtain a new master tag when restarted.
    
    // Prints the initial message
    Serial.println(F("-No Master Tag!-"));
    Serial.println(F("    SCAN NOW"));

    // readRFID will wait until a master card is scanned
    if (readRFID() == true) {
        myTags[tagsCount] = strdup(tagID.c_str()); // Sets the master tag into position 0 in the array
        Serial.println(F("Master Tag is Set!"));
        tagsCount++;
    }
    printNormalModeMessage();
}

/* ***********************************************************
 *                         Void Loop                         *
 * ********************************************************* */
void loop() {
    if (isTagPresent()==true){
        getTagID();
        checkTagID();
    } else {
        delay(50);
        //return;
    }
    
}    

/* ***********************************************************
 *                         Functions                         *
 * ********************************************************* */
bool isTagPresent(){
    /*  isTagPresent uses the MFRC522 methods to determine if 
     *    a tag is present or the read card serial is enabled.
     *  Parameters: (none)
     *  Returns:
     *    true  - if tag detected or read card serial is true
     *    false - no tag detected or no read card serial true
     */     
    bool returnValue = true;
    
    // NOT a new PICC_IsNewCardPresent in RFID reader
    //OR
    // NOT a PICC_ReadCardSerial active in Serial
    if ( !rfidReader.PICC_IsNewCardPresent() || !rfidReader.PICC_ReadCardSerial() ) { 
      returnValue = false;
    }
    return returnValue;
}

byte checkMyTags(String tagID){
    /* checkMyTags function loops through the array of myTags
     *   Parameters:
     *     tagID    - a string to look for
     *   Returns:
     *     tagIndex - index in the array of myTags
     *                default 0     
     */
    byte tagIndex = 0;
    //Serial.println("checkMyTags Started");
    // Zero is reserved for master tag
    for (int i = 1; i < 100; i++) {
        if (tagID == myTags[i]) { tagIndex = i; }
    }
    //Serial.println("checkMyTags ended");
    return tagIndex;
}

void checkTagID(){
    /* checkTagID check the tag ID for authorized tag ID values
     *   if Master tag found switch to program mode
     * Parameters: (none)
     * Returns: (none)
     */
    // Checks for Master tag
    if (tagID == myTags[0]) {
        // Switch to program mode
        Serial.println(F(" Program mode:"));
        Serial.println(F(" Add/Remove Tag"));
        
        // Now with timeout
        // readRFID will skip if timeout exceeded
        if (readRFID(timeout,true)==true) {
            //Check for authorized tag
            byte tagIndex = checkMyTags(tagID);
            if (tagIndex!=0){
                //Remove existing tag
                myTags[tagIndex] = '\0';
                Serial.println(F("  Tag Removed!"));
            } else {
                //Not existing, add tag
                myTags[tagsCount] = strdup(tagID.c_str());
                Serial.println(F("  Tag Added!"));
                tagsCount++;
            }
        } else {
            Serial.println(F("    timeout"));
        }
    } else { 
        //Check for authorized tag
        byte tagIndex = checkMyTags(tagID);
        if (tagIndex!=0){
            //Authorized tag
            Serial.println(F(" Access Granted!"));
        } else {
            //Not authorized tag
            Serial.println(F(" Access Denied!"));
            Serial.println(F(" New UID & Contents:"));
            rfidReader.PICC_DumpToSerial(&(rfidReader.uid));
        }
    }
    printNormalModeMessage();
}

bool getTagID() {
    /*  getTagID retrieves the tag ID.  Modifies global variable tagID
     *           
     *    Parameters: (none)    
     *    Returns: true
     */

    tagID = "";
    
    Serial.print(F(" UID tag: "));
    for (byte i = 0; i < rfidReader.uid.size; i++){
        // The MIFARE PICCs that we use have 4 byte UID
        Serial.print(rfidReader.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfidReader.uid.uidByte[i], HEX);
        // Adds the bytes in a single String variable
        tagID.concat(String(rfidReader.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tagID.concat(String(rfidReader.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.println();
    tagID.toUpperCase();
    rfidReader.PICC_HaltA();                     // Stop reading
    return true;
}

void printNormalModeMessage() {
    /*  printNormalModeMessage sends the standard greeting
     *    to the serial monitor.
     *  Parameters: (none)
     *  Returns: (none)
     */
    delay(1500);
    Serial.println();
    Serial.println(F("-Access Control-"));
    Serial.println(F(" Scan Your Tag!"));
}
