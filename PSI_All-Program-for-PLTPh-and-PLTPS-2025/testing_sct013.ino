#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(9600);
  ads.begin();
  ads.setGain(GAIN_ONE); // Input range ±4.096V, cocok untuk sensor 1V
}

void loop() {
  float maxValue = 0;
  float minValue = 32767;
  
  // Ambil 100 sampel sinyal AC
  for (int i = 0; i < 100; i++) {
    int16_t adc0 = ads.readADC_SingleEnded(0);  // pin A0 di ADS1115
    if (adc0 > maxValue) maxValue = adc0;
    if (adc0 < minValue) minValue = adc0;
    delay(5); // sampling delay
  }

  // Konversi dari bit ADC ke tegangan: 4.096V / 32768 ≈ 0.125 mV/bit
  float peakToPeak = (maxValue - minValue) * 0.125 / 1000.0; // Vpp dalam Volt
  float Vrms = (peakToPeak / 2.0) / sqrt(2); // konversi ke RMS
  float Irms = Vrms * 100.0;  // karena 1V = 100A untuk SCT-013-000 (100A:1V)

  Serial.print("Tegangan RMS: ");
  Serial.print(Vrms, 4);
  Serial.print(" V, Arus RMS: ");
  Serial.print(Irms, 3);
  Serial.println(" A");

  delay(1000);
}
