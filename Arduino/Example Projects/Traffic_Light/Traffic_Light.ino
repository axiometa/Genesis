#define LIGHT_RED 4
#define LIGHT_YELLOW 17
#define LIGHT_GREEN 16
#define BUTTON 8

void setup() {
  pinMode(LIGHT_RED, OUTPUT);
  pinMode(LIGHT_YELLOW, OUTPUT);
  pinMode(LIGHT_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  digitalWrite(LIGHT_RED, HIGH);
  digitalWrite(LIGHT_YELLOW, LOW);
  digitalWrite(LIGHT_GREEN, LOW);

  if (digitalRead(BUTTON) == LOW) {
    delay(1000);
    digitalWrite(LIGHT_RED, LOW);
    digitalWrite(LIGHT_YELLOW, HIGH);
    delay(1000);
    digitalWrite(LIGHT_YELLOW, LOW);
    digitalWrite(LIGHT_GREEN, HIGH);
    delay(1500);
    for (int i = 0; i < 3; i++) {
      digitalWrite(LIGHT_GREEN, HIGH);
      delay(500);
      digitalWrite(LIGHT_GREEN, LOW);
      delay(500);
    }
    digitalWrite(LIGHT_YELLOW, HIGH);
    delay(1000);
    digitalWrite(LIGHT_YELLOW, LOW);
  }
}
