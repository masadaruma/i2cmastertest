#include <Wire.h>

#define SSONIC_ADDRESS 0x27
#define SLAVE_REGISTER_1 0x00
#define SLAVE_REGISTER_2 0x01

int val[16];
int valout;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(SSONIC_ADDRESS);
  Wire.write(SLAVE_REGISTER_1);
  Wire.endTransmission(false);
  Wire.requestFrom(SSONIC_ADDRESS, 2);
  Serial.print("SSONIC_REGISTER_1 ");
  byte i=0;
  while (Wire.available() > 0){
     val[i] = Wire.read();
     Serial.print(val[i]);Serial.print(" ");
     Serial.print(val[i],BIN);
     Serial.print(" ");        
     i++; 
  }
  Serial.print("dist : ");
  valout = (val[0] << 8&0xFF00) | (val[1] << 0&0x00FF);
  Serial.println(valout);
  Serial.println(" "); 
delay(1000);
}