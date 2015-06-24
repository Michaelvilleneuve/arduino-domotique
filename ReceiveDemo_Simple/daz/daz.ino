/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int stepperPin = 5;
int dirPin = 6;
int sleepPin=4;
bool ouvert = true;

void setup() {
pinMode(dirPin, OUTPUT);
pinMode(stepperPin, OUTPUT);
digitalWrite(sleepPin, HIGH);
 
Serial.begin(9600);
mySwitch.enableReceive(0);
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 21585) {
     ouvrir();
    }
    else if (value == 21588){
      fermer();
    }

    mySwitch.resetAvailable();
  }
  pause();
}
void step(boolean dir,int steps)
 {
 digitalWrite(dirPin,dir);
 delay(50);
 for(int i=0;i<steps;i++)
 {
   digitalWrite(stepperPin, HIGH);
   delayMicroseconds(900);
   digitalWrite(stepperPin, LOW);
   delayMicroseconds(900);
 }
  }

void fermer()
{
   if(ouvert == true){
  digitalWrite(sleepPin, HIGH);
  step(true,200);
  pause();
  ouvert = false;
   }
}


void ouvrir()
{
  if(ouvert == false){
  digitalWrite(sleepPin, HIGH);
 step(false,200);
  pause();
  ouvert = true;
  }
}

void pause()
{
  digitalWrite(sleepPin, LOW);
  delay(100);
//digitalWrite(sleepPin, HIGH);
}

