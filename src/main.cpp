#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
boolean oldPinState = LOW;
const int buttonPin = G37;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {
  if (bleKeyboard.isConnected()) {
    if (digitalRead(buttonPin) == HIGH) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high
      if (oldPinState == LOW) {
        //if the old Pin state was LOW and the button pin is HIGH than...
        //send the spacebar
        bleKeyboard.print(" ");
        Serial.println("BUTTON PRESSED");

        // gold
        bleKeyboard.press(KEY_LEFT_SHIFT);
        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press('a');
        bleKeyboard.releaseAll();
        // bleKeyboard.println("AT+BleKeyboardCode=02-00-39-00-00-00-00"); // shift + caps lock
        // ble.println("AT+BleKeyboardCode=02-00-04-00-00-00-00"); // shift + a
        // ble.println("AT+BleKeyboardCode=00-00");

        // if (ble.waitForOK())
        // {
        //   Serial.println(F("OK!"));
        // }
        // else
        // {
        //   Serial.println(F("FAILED!"));
        // }

        delay(500);        //or you can comment this one out, and it will send the newline character
            //bleKeyboard.write(KEY_RETURN);
      }
      oldPinState = HIGH;
    }
    else {
      oldPinState = LOW;
    }
  }
  delay(10);
}