/* Ce programme reconnait la luminosite, allume une petite lampe s'il y a peu de luminosite, capte la temperature */
#include <SPI.h>
#include <Ethernet.h>
#include <RCSwitch.h>
#include <dht.h>
#define dht_dpin A0
#define lampe1 1361
#define lampe10 1364
#define lampe2 4433
#define lampe20 4436
#define lampe3 5201
#define lampe30 5204
#define lampe4 1119505
#define lampe40 1119508
#define temp 21585
#define ouverture 86356
#define verrouferme 1231323
#define verouillage 123138
#define mouvement 341004
dht DHT;
int pirState = LOW;
int capteurlum = 5;
int lum1 = 0; 
int inputPin = 3; 
const int buttonPin = 13;
String page;
String action;
int val = 0; 
RCSwitch mySwitch = RCSwitch();
byte mac[] = {
  0xDA, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 17);
EthernetClient client;
IPAddress server(192, 168, 1, 7);





void setup() {
  // pin beep
    pinMode(buttonPin, OUTPUT);  
   pinMode(inputPin, INPUT);
  pinMode(9, OUTPUT);
  beep(50); 
  mySwitch.enableReceive(0);
  Serial.begin(9600);
  delay(1000);
 if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP Probleme");
    beep(50);
    beep(50);
    beep(50);
    Ethernet.begin(mac, ip);
  }
  Serial.println("Fin de parametrage...");
}


void loop(){
   ecouter433();
}
void envoyerrequete(String page, String action, int val) {
  DHT.read11(dht_dpin);
  float tempe = DHT.temperature;
  float hum = DHT.humidity;
  client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connexion...");
    client.println("GET /"+ page +".php?auto=a&q=ajax&action="+ action+"&temp="+tempe+"&hum="+hum+"&val="+val+" HTTP/1.1");
    client.println("Host: 192.168.1.7");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("Echec connexion");
  }
}
void ecouter433() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    Serial.println(value);
   switch(value) {
     case lampe1:
     envoyerrequete("index","lampe1",1);
     mySwitch.resetAvailable();
     delay(500);
     break;
      case temp:
     envoyerrequete("index","temp",1);
     mySwitch.resetAvailable();
     delay(500);
     break;
     case lampe2:
     envoyerrequete("index","lampe2",1);
     mySwitch.resetAvailable();
     delay(500);    
     break;
     case lampe3:
     envoyerrequete("index","lampe3",1);
     mySwitch.resetAvailable();
     delay(500);  
     break;
     case lampe4:
     envoyerrequete("index","lampe4",1);
     mySwitch.resetAvailable();
     delay(500);
     break;
     case lampe10:
     envoyerrequete("index","lampe1",0);
     mySwitch.resetAvailable();
     delay(500);
     break;
     case lampe20:
     envoyerrequete("index","lampe2",0); 
     mySwitch.resetAvailable();
      delay(500);   
     break;
     case lampe30:
     envoyerrequete("index","lampe3",0);
     mySwitch.resetAvailable();
     delay(500);  
     break;
     case lampe40:
     envoyerrequete("index","lampe4",0);
     mySwitch.resetAvailable();
     delay(500);
     break;
     case ouverture:
       digitalWrite(buttonPin, HIGH);
       delay(1000);
       digitalWrite(buttonPin, LOW); 
     break;
     case mouvement:
     Serial.println("mouvement");
                   val = digitalRead(inputPin);
                  if (val == HIGH) {            // check if the input is HIGH
                    if (pirState == LOW) {
                      Serial.println("mouvement envoi");
                      envoyerrequete("index","mouvement", 1);
                      pirState = HIGH;
                    }
                  } else {
                    if (pirState == HIGH){
                      // we have just turned of
                      Serial.println("Plus de mouvement");
                      // We only want to print on the output change, not state
                      pirState = LOW;
                    }
                  }
     break;
     default:
     //
     break;
   }
    mySwitch.resetAvailable();
  }
}
/** BIP **/ 
void beep(unsigned char delayms){
  analogWrite(9, 20);
  delay(delayms);  
  analogWrite(9, 0); 
  delay(delayms);
}  
