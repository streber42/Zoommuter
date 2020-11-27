#include <Arduino.h>
#include <BleKeyboard.h>
#include <M5StickC.h>
#include "AXP192.h"
TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

BleKeyboard bleKeyboard;
boolean oldPinState = LOW;
const int buttonPin = G37;
void print_wakeup_reason();
void setup() {
  // Serial.begin(115200);
  // Serial.println("Starting BLE work!");
  m5.begin(false);
  // M5.Lcd.setRotation(3);
  // tftSprite.createSprite(160, 80);
  // tftSprite.setRotation(3);
  M5.Axp.EnableCoulombcounter();
  bleKeyboard.begin();
  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, 0); //1 = High, 0 = Low
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
  print_wakeup_reason();
  // delay(1000);

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
  Serial.println("Going to sleep now");
    M5.Axp.LightSleep(1000000);
  }

  M5.Axp.SetChargeCurrent(CURRENT_100MA);

  M5.update();
  //Go to sleep now
  // Serial.flush();
}

// /*
// Deep Sleep with External Wake Up
// =====================================
// This code displays how to use deep sleep with
// an external trigger as a wake up source and how
// to store data in RTC memory to use it over reboots

// This code is under Public Domain License.

// Hardware Connections
// ======================
// Push Button to GPIO 33 pulled down with a 10K Ohm
// resistor

// NOTE:
// ======
// Only RTC IO can be used as a source for external wake
// source. They are pins: 0,2,4,12-15,25-27,32-39.

// Author:
// Pranav Cherukupalli <cherukupallip@gmail.com>
// */
// /*
// #define BUTTON_PIN_BITMASK 0x2000000000 // 2^37 in hex

// RTC_DATA_ATTR int bootCount = 0;

// /*
// Method to print the reason by which ESP32
// has been awaken from sleep
// */
// /*
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0: Serial.println("Wakeup caused by external signal using RTC_IO"); break;
  case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
  case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
  case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
  case ESP_SLEEP_WAKEUP_ULP: Serial.println("Wakeup caused by ULP program"); break;
  default: Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

// void setup() {
//   Serial.begin(115200);
//   bleKeyboard.begin();
//   delay(1000); //Take some time to open up the Serial Monitor

//   //Increment boot number and print it every reboot
//   ++bootCount;
//   Serial.println("Boot number: " + String(bootCount));

//   if (bleKeyboard.isConnected()) {
//     bleKeyboard.press(KEY_LEFT_SHIFT);
//     bleKeyboard.press(KEY_LEFT_GUI);
//     bleKeyboard.press('a');
//     bleKeyboard.releaseAll();
//   }

//   //Print the wakeup reason for ESP32
//   print_wakeup_reason();

//   /*
//   First we configure the wake up source
//   We set our ESP32 to wake up for an external trigger.
//   There are two types for ESP32, ext0 and ext1 .
//   ext0 uses RTC_IO to wakeup thus requires RTC peripherals
//   to be on while ext1 uses RTC Controller so doesnt need
//   peripherals to be powered on.
//   Note that using internal pullups/pulldowns also requires
//   RTC peripherals to be turned on.
//   */
//  /*
//   esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, 0); //1 = High, 0 = Low

//   //If you were to use ext1, you would use it like
//   //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

//   //Go to sleep now
//   Serial.println("Going to sleep now");
//   delay(1000);
//   esp_light_sleep_start();
//   // esp_deep_sleep_start();
//   Serial.println("This will never be printed");
// }

// void loop() {
//   //This is not going to be called
// }
// */