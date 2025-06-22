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
  Serial.begin(115200);
  Serial1.begin(115200);
  Wire.begin();

  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

  bme1.begin(0x76);
  bme2.begin(0x77);

  ads1.begin(0x48);
  ads1.setGain(GAIN_ONE);

  ads2.begin(0x49);
  ads2.setGain(GAIN_ONE);

  Serial2.begin(9600);
  Serial3.begin(9600);
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

  // Kirim data ke serial sebagai CSV horizontal, awali dengan '$' (Serial 0)
  Serial.print("$");
  Serial.print(lux); Serial.print(",");
  Serial.print(t1); Serial.print(","); Serial.print(h1); Serial.print(","); Serial.print(p1); Serial.print(",");
  Serial.print(t2); Serial.print(","); Serial.print(h2); Serial.print(","); Serial.print(p2); Serial.print(",");
  for (int i = 0; i < 4; i++) {
    Serial.print(ads1_vals[i]); Serial.print(",");
  }
  for (int i = 0; i < 4; i++) {
    Serial.print(ads2_vals[i]); Serial.print(",");
  }
  Serial.print(v1); Serial.print(","); Serial.print(i1); Serial.print(","); Serial.print(w1); Serial.print(",");
  Serial.print(e1); Serial.print(","); Serial.print(f1); Serial.print(","); Serial.print(pf1); Serial.print(",");
  Serial.print(v2); Serial.print(","); Serial.print(i2); Serial.print(","); Serial.print(w2); Serial.print(",");
  Serial.print(e2); Serial.print(","); Serial.print(f2); Serial.print(","); Serial.println(pf2);

  // Kirim data ke serial sebagai CSV horizontal, awali dengan '$' (Serial 1 Raspi)
  Serial1.print("$");
  Serial1.print(lux); Serial1.print(",");
  Serial1.print(t1); Serial1.print(","); Serial1.print(h1); Serial1.print(","); Serial1.print(p1); Serial1.print(",");
  Serial1.print(t2); Serial1.print(","); Serial1.print(h2); Serial1.print(","); Serial1.print(p2); Serial1.print(",");
  for (int i = 0; i < 4; i++) {
    Serial1.print(ads1_vals[i]); Serial1.print(",");
  }
  for (int i = 0; i < 4; i++) {
    Serial1.print(ads2_vals[i]); Serial1.print(",");
  }
  Serial1.print(v1); Serial1.print(","); Serial1.print(i1); Serial1.print(","); Serial1.print(w1); Serial1.print(",");
  Serial1.print(e1); Serial1.print(","); Serial1.print(f1); Serial1.print(","); Serial1.print(pf1); Serial1.print(",");
  Serial1.print(v2); Serial1.print(","); Serial1.print(i2); Serial1.print(","); Serial1.print(w2); Serial1.print(",");
  Serial1.print(e2); Serial1.print(","); Serial1.print(f2); Serial1.print(","); Serial1.println(pf2);

  delay(3000);
}
