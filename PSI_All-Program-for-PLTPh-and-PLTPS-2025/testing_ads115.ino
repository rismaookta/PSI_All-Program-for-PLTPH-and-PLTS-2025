#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  // Buat objek untuk ADS1115

void setup() {
  Serial.begin(9600);
  ads.begin();         // Mulai komunikasi I2C dengan ADS1115
}

void loop() {
  int16_t adc0 = ads.readADC_SingleEnded(0);  // Baca input dari kanal A0
  float voltage = adc0 * 0.1875 / 1000;        // Konversi ke volt (0.1875 mV/bit @gain=2/3)
  
  Serial.print("ADC Reading: ");
  Serial.print(adc0);
  Serial.print(" | Tegangan: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(1000);
}
