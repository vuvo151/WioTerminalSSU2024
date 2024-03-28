void setup() {
  pinMode(WIO_BUZZER, OUTPUT);
}

void loop() {
  analogWrite(WIO_BUZZER, 100);
  delay(1000);
  analogWrite(WIO_BUZZER, 0);
  delay(1000);
}
