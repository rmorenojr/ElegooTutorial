//www.elegoo.com
//2016.12.08
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
float a;

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void loop() {
  long pingDuration;   
   
   a=sr04.Distance();
   pingDuration = sr04.pingTime();
   Serial.print(a);
   Serial.println("cm");
   Serial.print(pingDuration);
   Serial.println(" round trip in microseconds");
   delay(1000);
}
