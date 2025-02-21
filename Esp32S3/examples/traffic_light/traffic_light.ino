const int redPin = 9; // Red LED pin
const int yellowPin = 39; // Yellow LED pin
const int greenPin = 40; // Green LED pin
void setup() {
pinMode(redPin, OUTPUT); // Set Red LED pin as output
pinMode(yellowPin, OUTPUT); // Set Yellow LED pin as output
pinMode(greenPin, OUTPUT); // Set Green LED pin as output
}
void loop() {
// Red light on for 5 seconds
digitalWrite(redPin, HIGH);
digitalWrite(yellowPin, LOW);
digitalWrite(greenPin, LOW);
delay(2000); // Wait for 2 seconds
// Yellow light on for 2 seconds
digitalWrite(redPin, LOW);
digitalWrite(yellowPin, HIGH);
digitalWrite(greenPin, LOW);
delay(500); // Wait for  0.5 seconds
// Green light on for 5 seconds
digitalWrite(redPin, LOW);
digitalWrite(yellowPin, LOW);
digitalWrite(greenPin, HIGH);
delay(2000); // Wait for 2 seconds
// Yellow light on for 2 seconds before returning to red
digitalWrite(redPin, LOW);
digitalWrite(yellowPin, HIGH);
digitalWrite(greenPin, LOW);
delay(500); // Wait for 0.5 seconds
}
