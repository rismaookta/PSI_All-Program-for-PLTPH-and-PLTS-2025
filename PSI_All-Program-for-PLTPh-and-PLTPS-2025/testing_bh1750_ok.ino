#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();

  Serial.println("BH1750 Test begin");
}

void loop() {
  float lux = lightMeter.readLightLevel();

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");

  delay(1000);
}
