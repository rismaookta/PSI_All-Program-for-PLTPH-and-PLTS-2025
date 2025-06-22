#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>
#include <PZEM004Tv30.h>

// Sensor globals
BH1750 lightMeter;
Adafruit_BME280 bme1;
Adafruit_BME280 bme2;
Adafruit_ADS1115 ads1;
Adafruit_ADS1115 ads2;
PZEM004Tv30 pzem1(&Serial2);
PZEM004Tv30 pzem2(&Serial3);

void setup() {
  Serial.begin(115200);    // Untuk debug ke PC
  Serial1.begin(115200);   // Kirim data ke Raspberry Pi via Serial1
  Serial2.begin(9600);     // Untuk PZEM1
  Serial3.begin(9600);     // Untuk PZEM2
  Wire.begin();

  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

  bme1.begin(0x76);
  bme2.begin(0x77);

  ads1.begin(0x48);
  ads1.setGain(GAIN_ONE);

  ads2.begin(0x49);
  ads2.setGain(GAIN_ONE);
}

void loop() {
  float lux = lightMeter.readLightLevel();

  // BME280 #1
  float t1 = bme1.readTemperature();
  float h1 = bme1.readHumidity();
  float p1 = bme1.readPressure() / 100.0F;

  // BME280 #2
  float t2 = bme2.readTemperature();
  float h2 = bme2.readHumidity();
  float p2 = bme2.readPressure() / 100.0F;

  // ADS1115 #1
  float ads1_vals[4];
  for (int i = 0; i < 4; i++) {
    ads1_vals[i] = ads1.computeVolts(ads1.readADC_SingleEnded(i));
  }

  // ADS1115 #2
  float ads2_vals[4];
  for (int i = 0; i < 4; i++) {
    ads2_vals[i] = ads2.computeVolts(ads2.readADC_SingleEnded(i));
  }

  // PZEM004T #1
  float v1 = pzem1.voltage();
  float i1 = pzem1.current();
  float w1 = pzem1.power();
  float e1 = pzem1.energy();
  float f1 = pzem1.frequency();
  float pf1 = pzem1.pf();

  // PZEM004T #2
  float v2 = pzem2.voltage();
  float i2 = pzem2.current();
  float w2 = pzem2.power();
  float e2 = pzem2.energy();
  float f2 = pzem2.frequency();
  float pf2 = pzem2.pf();

  // Format CSV dimulai dengan tanda $
  String data = "$";
  data += String(lux) + ",";
  data += String(t1) + "," + String(h1) + "," + String(p1) + ",";
  data += String(t2) + "," + String(h2) + "," + String(p2) + ",";

  for (int i = 0; i < 4; i++) {
    data += String(ads1_vals[i]) + ",";
  }
  for (int i = 0; i < 4; i++) {
    data += String(ads2_vals[i]) + ",";
  }

  data += String(v1) + "," + String(i1) + "," + String(w1) + ",";
  data += String(e1) + "," + String(f1) + "," + String(pf1) + ",";
  data += String(v2) + "," + String(i2) + "," + String(w2) + ",";
  data += String(e2) + "," + String(f2) + "," + String(pf2);

  // Kirim ke Raspberry Pi lewat Serial1
  Serial1.println(data);

  // (Optional) tampilkan juga ke Serial Monitor di PC
  Serial.println(data);

  delay(3000);
}
