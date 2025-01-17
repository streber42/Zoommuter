#include <Arduino.h>
#include <BleKeyboard.h>
#include <M5StickC.h>
#include "AXP192.h"
TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

BleKeyboard bleKeyboard;
boolean oldPinState = LOW;
const int buttonPin = G37;

void setup() {
  // Serial.begin(115200);
  // Serial.println("Starting BLE work!");
  m5.begin(false);
  // M5.Lcd.setRotation(3);
  // tftSprite.createSprite(160, 80);
  // tftSprite.setRotation(3);
  M5.Axp.EnableCoulombcounter();
  bleKeyboard.begin();
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {
  // tftSprite.fillSprite(BLACK);
  // tftSprite.setCursor(0, 0, 1);
  // tftSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
  // tftSprite.setCursor(0, 10);
  // tftSprite.printf("Bat:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
  // tftSprite.setCursor(0, 30);
  // tftSprite.printf("USB:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
  // tftSprite.setCursor(0, 50);
  // tftSprite.printf("5V-In:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVinVoltage(), M5.Axp.GetVinCurrent());
  // tftSprite.setCursor(0, 70);
  // tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
  // tftSprite.pushSprite(0, 0);
  Serial.println(M5.Axp.GetVBusCurrent());

  // 0x01 long press(1s), 0x02 press
  if (M5.Axp.GetBtnPress() == 0x02)
  {
    esp_restart();
  }

  if (M5.BtnA.wasPressed())
  {
    // close tft voltage output
    // M5.Axp.SetLDO2(false);
    // close tft lcd voltage output
    // M5.Axp.SetLDO3(false);
    if (bleKeyboard.isConnected()) {
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('a');
      bleKeyboard.releaseAll();
    }
  }

  if (M5.BtnB.wasPressed()) {
    M5.Axp.SetLDO2(false);
    M5.Axp.SetLDO3(false);
  }

  M5.Axp.SetChargeCurrent(CURRENT_100MA);

  M5.update();
  delay(100);
}