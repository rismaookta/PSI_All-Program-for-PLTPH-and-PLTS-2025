// Program untuk membaca BH1750, 2x ADS1115, dan 2x BME280 pada Arduino Mega 2560
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ADS1X15.h>
#include <BH1750.h>

// Inisialisasi objek sensor
Adafruit_BME280 bme1; // BME280 pertama
Adafruit_BME280 bme2; // BME280 kedua
Adafruit_ADS1115 ads1; // Alamat default 0x48
Adafruit_ADS1115 ads2; // Alamat kedua 0x49
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Inisialisasi BH1750
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Gagal menginisialisasi BH1750");
  } else {
    Serial.println("BH1750 berhasil diinisialisasi");
  }

  // Inisialisasi BME280 #1 di 0x76
  if (!bme1.begin(0x76)) {
    Serial.println("Gagal menginisialisasi BME280 #1 di 0x76");
  } else {
    Serial.println("BME280 #1 berhasil diinisialisasi");
  }

  // Inisialisasi BME280 #2 di 0x77
  if (!bme2.begin(0x77)) {
    Serial.println("Gagal menginisialisasi BME280 #2 di 0x77");
  } else {
    Serial.println("BME280 #2 berhasil diinisialisasi");
  }

  // Inisialisasi ADS1115 #1 di 0x48
  if (!ads1.begin(0x48)) {
    Serial.println("Gagal menginisialisasi ADS1115 #1 di 0x48");
  } else {
    Serial.println("ADS1115 #1 berhasil diinisialisasi");
  }

  // Inisialisasi ADS1115 #2 di 0x49
  if (!ads2.begin(0x49)) {
    Serial.println("Gagal menginisialisasi ADS1115 #2 di 0x49");
  } else {
    Serial.println("ADS1115 #2 berhasil diinisialisasi");
  }
}

void loop() {
  // Baca data dari BH1750
  float lux = lightMeter.readLightLevel();
  Serial.print("Cahaya (lux): "); Serial.println(lux);

  // Baca data dari BME280 #1
  Serial.println("-- BME280 #1 --");
  Serial.print("Temp: "); Serial.print(bme1.readTemperature()); Serial.println(" *C");
  Serial.print("Hum: "); Serial.print(bme1.readHumidity()); Serial.println(" %");
  Serial.print("Pres: "); Serial.print(bme1.readPressure() / 100.0F); Serial.println(" hPa");

  // Baca data dari BME280 #2
  Serial.println("-- BME280 #2 --");
  Serial.print("Temp: "); Serial.print(bme2.readTemperature()); Serial.println(" *C");
  Serial.print("Hum: "); Serial.print(bme2.readHumidity()); Serial.println(" %");
  Serial.print("Pres: "); Serial.print(bme2.readPressure() / 100.0F); Serial.println(" hPa");

  // Baca semua channel ADS1115 #1
  Serial.println("-- ADS1115 #1 --");
  for (int i = 0; i < 4; i++) {
    int16_t val = ads1.readADC_SingleEnded(i);
    float voltage = val * 0.1875 / 1000.0; // default gain = 2/3
    Serial.print("AIN"); Serial.print(i); Serial.print(": "); Serial.print(voltage); Serial.println(" V");
  }

  // Baca semua channel ADS1115 #2
  Serial.println("-- ADS1115 #2 --");
  for (int i = 0; i < 4; i++) {
    int16_t val = ads2.readADC_SingleEnded(i);
    float voltage = val * 0.1875 / 1000.0;
    Serial.print("AIN"); Serial.print(i); Serial.print(": "); Serial.print(voltage); Serial.println(" V");
  }

  Serial.println("=====================================");
  delay(2000);
}
