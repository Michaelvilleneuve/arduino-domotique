/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  pinMode(0,INPUT);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
 Serial.println(digitalRead(2));
}
