#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // default address is 0x77 or 0x76

void setup() {
  Serial.begin(9600);
  Wire.begin();

  bool status;

  // Coba inisialisasi dengan alamat 0x76
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("BME280 @0x76 not found. Trying 0x77...");
    status = bme.begin(0x77);
  }

  if (!status) {
    Serial.println("BME280 not found at 0x76 or 0x77. Check wiring!");
    while (1); // Hentikan program
  } else {
    Serial.println("BME280 detected.");
  }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println("---------------------------");
  delay(2000);
}
