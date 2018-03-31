/* Graphic crosshairs with analog joystick
 *  by Ricardo Moreno
 *  03/15/2018
 * 
 */
/* ****************** INCLUDE LIBRARIES ********************** */
#include <U8g2lib.h>
#include <toneAC.h>               // ToneAC works on pins 9 and 10

/* ******************* GLOBAL CONSTANTS ********************** */
// Analog Joystick
const PROGMEM int X_pin = A1;     // analog pin connected to X output
const PROGMEM int Y_pin = A0;     // analog pin connected to Y output
const PROGMEM int FIRE_BUT2 = 2;  // digital pin connected to switch output

//Tactile switch
const PROGMEM int FIRE_BUT = A2;

//Passive buzzer
const PROGMEM byte spkr_pos = 9;
const PROGMEM byte spkr_neg = 10;

// OLED Pins
// A byte can hold a number up to 255
const PROGMEM byte OLED_CLK = 13;           //SCK system clock or SCL
const PROGMEM byte OLED_MOSI = 11;          //MOSI or SDA
const PROGMEM byte OLED_RES = 8;           //Reset
const PROGMEM byte OLED_DC = 7;             //Data Communication
const PROGMEM byte OLED_CS = 6;             //Component Select
//Instantiate U8G2 object class - Plus Pins
//There is only one small difference between SSD1306 and SH1106: The SH1106 controller has an internal RAM of 132x64 pixel
//SSD1306
//U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI oled(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SSD1306_128X64_NONAME_2_4W_SW_SPI oled(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI oled(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES); 
//U8G2_SSD1306_128X64_NONAME_2_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES); 
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES); 
//SH1106
//U8G2_SH1106_128X64_NONAME_1_4W_SW_SPI oled(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SH1106_128X64_NONAME_2_4W_SW_SPI oled(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI oled(U8G2_R0, /* clock=*/ OLED_CLK, /* data=*/ OLED_MOSI, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
//U8G2_SH1106_128X64_NONAME_2_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI oled(U8G2_R0, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RES);

const int MAXSCREEN_WIDTH PROGMEM = 128;  //0-127
const int MAXSCREEN_HEIGHT PROGMEM = 64;  //0-63
const int MAXANALOG_VALUE PROGMEM = 1023; //0-1023

/* ******************* GLOBAL VARIABLES ********************** */
int cursor_height = 20;
int cursor_width = 20;
int Xvalue = 512;
int Yvalue = 512;
bool Switchvalue = HIGH;

/* *******************************************************
 *                         Setup
 ********************************************************* */
void setup() {
  pinMode(FIRE_BUT2, INPUT_PULLUP);
  pinMode(FIRE_BUT, INPUT_PULLUP);
  //Serial.begin(9600);
  //OLED Diplay
  /* U8g2 Project: SSD1306 or SH1106 OLED SPI Board */
  oled.begin();
  oled.clear();
  oled.setBitmapMode(1);
}

/* *******************************************************
 *                       Void Loop
 ********************************************************* */
void loop() {
  if ((!digitalRead(FIRE_BUT))||(!digitalRead(FIRE_BUT2))){
    Switchvalue = false;
  }else{
    Switchvalue = true;
  }
  Xvalue = analogRead(X_pin);
  Yvalue = analogRead(Y_pin);
  //Serial.print("Switch:  ");
  //Serial.print(Switchvalue);
  //Serial.print("   X-axis: ");
  //Serial.print(Xvalue);
  //Serial.print("   Y-axis: ");
  //Serial.println(Yvalue);
  //Serial.print("\n");
  oled.clearBuffer();
  draw(Xvalue, Yvalue, Switchvalue);
  oled.sendBuffer();
  //delay(100);
}

/* *******************************************************
 *                       Functions
 ********************************************************* */

 void draw(int x, int y, bool sw){
  x = map(x,MAXANALOG_VALUE,0,0,MAXSCREEN_WIDTH-1);
  y = map(y,0,MAXANALOG_VALUE,0,MAXSCREEN_HEIGHT-1);
  //Serial.print("X = "); Serial.print(x); Serial.print("  Y = "); Serial.println(y);
  //oled.drawVLine(x, y-cursor_height/2, cursor_height);
  oled.drawVLine(x,0,MAXSCREEN_HEIGHT-1);
  //oled.drawHLine(x-cursor_width/2, y, cursor_width);
  oled.drawHLine(0, y, MAXSCREEN_WIDTH-1);
  if (sw){
    oled.drawCircle(x, y, 10, U8G2_DRAW_ALL);
  } else {
    //toneAC(frequency, volume, length , background)
    toneAC(600,5,200,true);
    oled.drawDisc(x, y, 10, U8G2_DRAW_ALL);
  }
}

