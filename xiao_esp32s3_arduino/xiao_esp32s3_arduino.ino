#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad("AnumaGamePad");
#define VERT_PIN D1
#define HORZ_PIN D2

void setup() {
  Serial.begin(115200);
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  // pinMode(SEL_PIN, INPUT_PULLUP);


  //ゲームパッド設定
  BleGamepadConfiguration bleGamepadConfig;
  // bleGamepadConfig.setAutoReport(false);
  // bleGamepadConfig.setControllerType(CONTROLLER_TYPE_MULTI_AXIS);
  // bleGamepadConfig.setButtonCount(numOfButtons);
  bleGamepad.begin(&bleGamepadConfig);


  Serial.println("");
  Serial.println("Hello, XIAO ESP32-S3!");
}

void loop() {
  // if (true)
  if (bleGamepad.isConnected())
  {
      int left_vert = analogRead(VERT_PIN);
      int left_horz = analogRead(HORZ_PIN);
      int gamepad_left_vert = convertAnalogToGamepadAxis(left_vert);
      int gamepad_left_horz = convertAnalogToGamepadAxis(left_horz);

      Serial.print("left_vert: ");
      Serial.print(left_vert);
      Serial.print(", gamepad_left_vert: ");
      Serial.println(gamepad_left_vert);

      Serial.print("left_horz: ");
      Serial.print(left_horz);
      Serial.print(", gamepad_left_horz: ");
      Serial.println(gamepad_left_horz);
      // Serial.println("Press buttons 5, 16 and start. Move all enabled axes to max. Set DPAD (hat 1) to down right.");
      bleGamepad.setAxes(gamepad_left_vert, gamepad_left_horz, 32767, 32767, 32767, 32767, 32767, 32767);       //(X, Y, Z, RX, RY, RZ)
      //bleGamepad.setHIDAxes(32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767);  //(X, Y, Z, RZ, RX, RY)
      delay(10);

      // bleGamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);           //(X, Y, Z, RX, RY, RZ)
      // bleGamepad.setHIDAxes(0, 0, 0, 0, 0, 0, 0, 0);      //(X, Y, Z, RZ, RX, RY)
      // delay(500);
  }

  // int vert = analogRead(VERT_PIN);
  // int horz = analogRead(HORZ_PIN);
  // Serial.print("vert: ");
  // Serial.println(vert);
  // Serial.print("horz: ");
  // Serial.println(horz);
}

// 可変抵抗のアナログ値をゲームパッドの軸値に変換する関数
int convertAnalogToGamepadAxis(int analogValue) {
  int min_val = 0;
  int max_val = 4095;
  // 変換
  int mapped = map(analogValue, min_val, max_val, -32767, 32767);
  return mapped;
}