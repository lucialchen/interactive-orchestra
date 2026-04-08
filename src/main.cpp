#include <Arduino.h>

const int TOUCH_PINS[] = {33, 13, 12, 15, 2};
const int NUM_INSTRUMENTS = 5;
const int MODE_PIN = 32;
const int TOUCH_THRESHOLD = 25;

const char* INSTRUMENT_NAMES[] = {"flute", "tambourine", "lyre", "clarinet", "horn"};

// Mode 0 = single, Mode 1 = loop
int currentMode = 0;
bool wasActive[NUM_INSTRUMENTS] = {false};
bool modeWasActive = false;

unsigned long lastModeToggle = 0;
const int MODE_DEBOUNCE_MS = 400;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("READY");
}

void loop() {
  unsigned long now = millis();

  int modeVal = touchRead(MODE_PIN);
  bool modeTouched = modeVal < TOUCH_THRESHOLD;

  if (modeTouched && !modeWasActive && (now - lastModeToggle > MODE_DEBOUNCE_MS)) {
    currentMode = (currentMode + 1) % 2;
    lastModeToggle = now;
    Serial.print("MODE:");
    Serial.println(currentMode);
  }
  modeWasActive = modeTouched;

  for (int i = 0; i < NUM_INSTRUMENTS; i++) {
    int val = touchRead(TOUCH_PINS[i]);
    bool touched = val < TOUCH_THRESHOLD;

    if (touched && !wasActive[i]) {
      Serial.print(currentMode);
      Serial.print(",");
      Serial.println(INSTRUMENT_NAMES[i]);
    }

    wasActive[i] = touched;
  }

  delay(20);
}

// Test code for touch pin sensors
// #include <Arduino.h>

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   Serial.println("READY");
// }

// void loop() {
//   Serial.print("33:"); Serial.print(touchRead(33));
//   Serial.print("  13:"); Serial.print(touchRead(13));
//   Serial.print("  12:"); Serial.print(touchRead(12));
//   Serial.print("  15:"); Serial.print(touchRead(15));
//   Serial.print("  2:"); Serial.print(touchRead(2));
//   Serial.print("  32:"); Serial.println(touchRead(32));
//   delay(200);
// }