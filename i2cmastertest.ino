#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SSONIC_ADDRESS 0x27
#define SCREEN_ADDRESS 0x3C
#define SLAVE_REGISTER_1 0x00
#define SLAVE_REGISTER_2 0x01
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int val[16];
int valout;

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.invertDisplay(1);
  display.display();
  delay(2000); // Pause for 2 seconds
  display.invertDisplay(0);
  // Clear the buffer
}

void loop()
{
  Wire.beginTransmission(SSONIC_ADDRESS);
  Wire.write(SLAVE_REGISTER_1);
  Wire.endTransmission(false);
  Wire.requestFrom(SSONIC_ADDRESS, 2);
  Serial.print("SSONIC_REGISTER_1 ");
  byte i = 0;
  while (Wire.available() > 0)
  {
    val[i] = Wire.read();
    Serial.print(val[i]);
    Serial.print(" ");
    Serial.print(val[i], BIN);
    Serial.print(" ");
    i++;
  }
  Serial.print("dist : ");
  valout = (val[0] << 8 & 0xFF00) | (val[1] << 0 & 0x00FF);
  Serial.println(valout);
  Serial.println(" ");
  showdist();
  delay(200);
}

void showdist(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,0);
  display.println(F(" distance"));
  if(valout!=-1){
  display.setTextSize(4);display.print(" ");
  display.println(valout);
  }else{
    display.setTextSize(2);
    display.print("  out of \n   range.");
  }
  display.display();
}

