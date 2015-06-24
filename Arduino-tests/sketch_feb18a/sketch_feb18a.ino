/*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>
#include <Ethernet.h> 

RCSwitch mySwitch = RCSwitch();
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(212,1,212,10);  // Notre site tiptopboards.com a pour IP = 212.1.212.10

// Initialiser la librairie Ethernet client avec cette adresse IP, port 80 par défaut
EthernetClient client;


void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);
 if (Ethernet.begin(mac) == 0) {  //Démarre la connexion Ethernet
    Serial.println("Echec de configuration Ethernet avec DHCP");
    // plus rien à faire
    for(;;)
      ;
  }
  //Laisser une seconde au shield Ethernet pour s'initialiser
  delay(1000);
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
       if (client.connect(server, 80)) {  //Si ça se connecte
      Serial.println("connexion OK");
      // Faire une requète HTTP:
      Serial.println("Envoi de requete  ...");

    
      client.println("GET /test_arduino.php HTTP/1.0");  //Demander une page précise du site (php)
      //client.println("GET /texte.txt HTTP/1.0");  //Exemple pour lister un fichier texte
      client.println("Host: tiptopboards.com");
      client.println();
  } 
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }
}///////////////////////////////
///////////////////////////////
///////////////////////////////
   //Utilise la libraire Ethernet

//Entrer l'adresse MAC (si elle est indiquée sur le shield)
//Par défaut celle ci convient 
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(212,1,212,10);  // Notre site tiptopboards.com a pour IP = 212.1.212.10

// Initialiser la librairie Ethernet client avec cette adresse IP, port 80 par défaut
EthernetClient client;

void setup() {
  Serial.begin(9600);   //Pour le serial monitor (écran du PC)
  Serial.println("Demo du shield Ethernet W5100");
  
  if (Ethernet.begin(mac) == 0) {  //Démarre la connexion Ethernet
    Serial.println("Echec de configuration Ethernet avec DHCP");
    // plus rien à faire
    for(;;)
      ;
  }
  //Laisser une seconde au shield Ethernet pour s'initialiser
  delay(1000);
  Serial.println("Connexion...");

  if (client.connect(server, 80)) {  //Si ça se connecte
    Serial.println("connexion OK");
    // Faire une requète HTTP:
    Serial.println("Envoi de requete  ...");

    
    client.println("GET /test_arduino.php HTTP/1.0");  //Demander une page précise du site (php)
    //client.println("GET /texte.txt HTTP/1.0");  //Exemple pour lister un fichier texte
    client.println("Host: tiptopboards.com");
    client.println();
  } 
  else {
    //Si on ne parvient pas à se connecte au serveur
    Serial.println("Echec de connexion");
