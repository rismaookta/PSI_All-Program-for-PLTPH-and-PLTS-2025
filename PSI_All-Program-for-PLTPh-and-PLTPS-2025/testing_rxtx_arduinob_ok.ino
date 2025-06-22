// Mega B - Penerima
void setup() {
  Serial.begin(9600);      // untuk monitor
  Serial1.begin(9600);     // untuk komunikasi dari Mega A
}

void loop() {
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    Serial.println("Dari Mega A: " + data);
  }
}
