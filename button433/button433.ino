
const int buttonPin = 13;
int a = 0;
void setup() {
  // put your setup code here, to run once:
   pinMode(buttonPin, OUTPUT);  
    digitalWrite(buttonPin, HIGH); 
    delay(3000);
}

void loop() {
  digitalWrite(buttonPin, LOW);
}
