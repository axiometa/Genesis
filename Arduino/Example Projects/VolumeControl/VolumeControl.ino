#include "USB.h"
#include "USBHIDConsumerControl.h"

USBHIDConsumerControl ConsumerControl;

const int potPin = 1; // Adjust if necessary based on your board
const int threshold = 50;

int previousPot = 0;

void setup() {
  Serial.begin(115200);

  ConsumerControl.begin();
  USB.begin();
  previousPot = analogRead(potPin);
}

void loop() {
  int currentPot = analogRead(potPin);
  int diff = currentPot - previousPot;

  if (diff > threshold) {
    ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
    ConsumerControl.release();
    Serial.println("Volume Up");
    previousPot = currentPot;
  }
  else if (diff < -threshold) {
    ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
    ConsumerControl.release();
    Serial.println("Volume Down");
    previousPot = currentPot;
  }

  delay(10);
}

