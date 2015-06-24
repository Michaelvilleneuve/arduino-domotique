Include IRremote.h

IRsend irsend;

void loop() {

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xFDB04F, 32);
      delay(40);
    }
  delay(5000);
}
