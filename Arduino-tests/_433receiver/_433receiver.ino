
#include <RCSwitch.h>
#define ouverture 123456789
#define fermeture 987654321

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);
}

void loop() {
 /* RECEPTION NUMERO 1 */
  if (mySwitch.available()) {
    int codeenvoye = mySwitch.getReceivedValue();
    if (mySwitch.available()) {
    switch (codeenvoye){
      case ouverture:
        ouvrirleverrou();
      break;
      case fermeture:
        fermerleverrou();
      break;
    }
    mySwitch.resetAvailable();
  }
  }
  
}
/*** TA PARTIE MOTEUR ***/
void ouvrirleverrou(){
}
void fermerleverrou(){
}
