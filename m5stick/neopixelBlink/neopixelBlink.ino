#include <M5StickC.h>
#include <driver/i2s.h>
#include <NeoPixelBus.h>

#define PIN 26
#define NUMPIXELS 60

RgbColor white(225);
RgbColor black(0);

int sleepTime = 20;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(NUMPIXELS, PIN);

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(10);
  
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);
  
  strip.Begin();
  strip.Show();
  
  Serial.println();
  Serial.println("Running...");
}

void loop() {
  M5.update();
  
  delay(sleepTime);

  if (M5.BtnA.pressedFor(500)) {
    if(sleepTime <= 1000) {
      sleepTime++; 
    }
  }
  if (M5.BtnB.pressedFor(500)) {
    if(10 <= sleepTime) {
      sleepTime--;
    }
  }
  
  for(uint16_t i=0; i<NUMPIXELS; i++) {
      strip.SetPixelColor(i, white);
  }

  strip.Show();

  delay(sleepTime);
  
  for(uint16_t l=0; l<NUMPIXELS; l++) {
    strip.SetPixelColor(l, black);
  }

  strip.Show();

  // LCD
  M5.Lcd.fillScreen(BLACK);
  
  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("NeoPixel \nBLINK");
  
  M5.Lcd.setCursor(2, 36);
  M5.Lcd.printf("Delay : %i", sleepTime);
  Serial.println(sleepTime);
}
