
#include <RCSwitch.h>
#define ouverture 1380689
#define fermeture 1380692
#define pinreception 0
#define pinenvoi 4
#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
int Steps = 0;
boolean Direction = true;// gre
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;

RCSwitch mySwitch = RCSwitch();
float tempC = 0;
float tempf = 0; 
int tempPin = 0;
float samples[8];
float maxi = 0,mini = 100; 
int i;

void setup() {
   pinMode(7, OUTPUT);
  beep(50);
  beep(50);
  beep(50);
  delay(1000);
  Serial.begin(9600);
    pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  mySwitch.enableReceive(pinreception);
  mySwitch.enableTransmit(pinenvoi);
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT);  
}

void loop() {
  ecouter433();
  calculdistance();
 // calcultemp();
}
/*** FIN DE LOOP ***/
/** TEMP **/
void calcultemp() { 
  i++;
  if(i>1000){
   Serial.print("Temperature non : ");                               // Print text to Serial monitor 
   Serial.println(( 4.4 * analogRead(tempPin) * 26) / 1024.0); 
   i=0;
  }  
}
/** BIP **/ 
void beep(unsigned char delayms){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  
/** OUVERTURE A DISTANCE **/
void ecouter433(){
   if (mySwitch.available()) {
    int codeenvoye = mySwitch.getReceivedValue();

         
    if (mySwitch.available()) {
    switch (codeenvoye){
      case ouverture:
         Serial.println("Ouverture.");
      beep(50);
      beep(50);
        if(ouvrirleverrou()){
           succes();
           
        }
        else{
          echec(1);
        }   
      break;
      case fermeture:
      Serial.println("Fermeture.");
      // Fonction de fermeture
     
       beep(100);
          beep(50);
        if(fermerleverrou()){
           succes();
        }
        else{
          echec(1);
        } 
      break;
      default:
        //Debug:Serial.print("Aucune fréquence reçue.");
      break;
    }
    
  }
  }
  mySwitch.resetAvailable();
}
/** CAPTEUR DE DISTANCE, OUVERTURE SI MOINS DE 5 CM **/
void calculdistance(){
    long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);
  
  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique
   
  if (distance < 4) { 
}
  else {   //Trop loin
  }
  //Hors de portée (duration)
  if ( distance <= 0){  
    //Serial.print(duration);
    Serial.println("Hors de portee");
  }
  else if (distance <= 10) {
    Serial.println("Verification...");
    delay(1000);
                  digitalWrite(trigPin, LOW);  
              delayMicroseconds(2); 
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
              digitalWrite(trigPin, LOW);
              
              // Calcul de l'écho
              duration = pulseIn(echoPin, HIGH);
              // Distance proportionnelle à la durée de sortie
              distance = duration*340/(2*10000);  //Vitesse du son théorique
                if (distance <= 5) {
    Serial.print("Ouverture...");
    
    if(ouvrirleverrou()){
      Serial.println("Verrou ouvert!  ");
       beep(50);
      beep(50);
    }
    else{
     Serial.println("Probleme.");
    }
    
    }
    else {
      Serial.println("stop.");
    }
    }
}
/** CODE A ENVOYER SI SUCCES **/
void succes(){
        Serial.println("OK.");
         
        //mySwitch.send("000000000001010100010001");
}
/** ECHEC ET NOUVELLE TENTATIVE **/
void echec(int methode){
         beep(50);
         beep(50);
        Serial.println("Stop.");
        //mySwitch.send("100011000001010100000000");
        if(methode == 1){
          if(ouvrirleverrou()){
             succes();
          }
          else{
           //Debug:Serial.print("Problème. Fin des tentatives");
            mySwitch.send("100011000001010001010010");
          } 
        }
        else{
          if(fermerleverrou()){
             succes();
          }
          else{
           //Debug:Serial.print("Problème. Fin des tentatives");
            mySwitch.send("100011000001010001010010");
          }
        }
}
/*** TA PARTIE MOTEUR ***/
int ouvrirleverrou(){
    while(steps_left>0){
  currentMillis = micros();
  if(currentMillis-last_time>=1000){
  stepper(1); 
  time=time+micros()-last_time;
  last_time=micros();
  steps_left--;
  }
  }
  delay(2000);
  Direction=!Direction;
  steps_left=4095;
  int resultat = true;
  return resultat;
  // Si possible : Renvoi la valeur true si le verrou s'est bien ouvert et false si echec
}
int fermerleverrou(){
  int resultat = true;
  return resultat;
  // Si possible : Renvoi la valeur true si le verrou s'est bien fermé et false si echec
}
void stepper(int xw){
  for (int x=0;x<xw;x++){
switch(Steps){
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
}
SetDirection();
}
} 
void SetDirection(){
if(Direction==1){ Steps++;}
if(Direction==0){ Steps--; }
if(Steps>7){Steps=0;}
if(Steps<0){Steps=7; }
}

