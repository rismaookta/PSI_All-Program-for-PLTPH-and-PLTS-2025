// Mega A - Pengirim
void setup() {
  Serial1.begin(9600);
}

void loop() {
  Serial1.println("Halo dari Mega A");
  delay(1000);  // kirim setiap 1 detik
}
