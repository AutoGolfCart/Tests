void setup() {
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

}

void loop() {
    digitalWrite(4, HIGH);

    delay(200);

    digitalWrite(4, LOW);

    delay(200);

    digitalWrite(5, HIGH);

    delay(200);

    digitalWrite(5, LOW);

    delay(200);


}