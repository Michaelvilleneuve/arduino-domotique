void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Test !");
  delay(2000);

}

