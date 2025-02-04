#include <FastLED.h>

// Configuration
#define LED_PIN          5
#define BUTTON_PIN       47  // Button connected to Pin 8
#define COLOR_ORDER      GRB
#define CHIPSET          WS2811
#define BRIGHTNESS       10

// Matrix dimensions
const uint8_t kMatrixWidth = 5;
const uint8_t kMatrixHeight = 5;

// Number of LEDs
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds[NUM_LEDS];

// Function to map XY coordinates to LED index
uint16_t XY(uint8_t x, uint8_t y) {
  // Simple row-major order mapping
  return (y * kMatrixWidth) + x;
}

// Define Dice Faces (5x5 grid)
const bool diceFaces[6][5][5] = {
  // Face 1
  {
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, true,  false, false},
    {false, false, false, false, false},
    {false, false, false, false, false}
  },
  // Face 2
  {
    {true,  false, false, false, false },
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false,  false, false, false, true }
  },
  // Face 3
  {
    {true,  false, false, false, false },
    {false, false, false, false, false},
    {false, false, true,  false, false},
    {false, false, false, false, false},
    {false,  false, false, false, true }
  },
  // Face 4
  {
    {true,  false, false,  false, true },
    {false, false, false, false, false},
    {false,  false, false,  false, false },
    {false, false, false, false, false},
    {true,  false, false,  false, true }
  },
  // Face 5
  {
    {true,  false, false,  false, true },
    {false, false, false, false, false},
    {false,  false, true,  false, false },
    {false, false, false, false, false},
    {true,  false, false,  false, true }
  },
  // Face 6
  {
    {true,  false, true,  false, true },
    {false,  false, false,  false, false },
    {false,  false, false,  false, false },
    {false,  false, false,  false, false },
    {true,  false, true,  false, true }
  }
};

// Function to display a specific dice face
void displayDiceFace(int faceIndex) {
  // Clear all LEDs
  FastLED.clear();

  // Calculate starting positions to center the 5x5 dice face
  int startX = (kMatrixWidth - 5) / 2;
  int startY = (kMatrixHeight - 5) / 2;

  // Light up LEDs based on the dice face pattern
  for(int y = 0; y < 5; y++) {
    for(int x = 0; x < 5; x++) {
      if(diceFaces[faceIndex][y][x]) {
        leds[XY(startX + x, startY + y)] = CRGB::White; // Set to white color
      }
    }
  }

  // Update the LED matrix
  FastLED.show();
}

// Function to perform the sparkle and transition to dice face
void sparkleAndDisplayDice(int faceIndex) {
  const int sparkleDuration = 1500; // Total duration of sparkle effect in ms
  const int sparkleInterval = 1;   // Initial interval between sparkles in ms
  unsigned long startTime = millis();
  int currentInterval = sparkleInterval;

  // Sparkle Phase: Randomly light up LEDs with decreasing speed
  while (millis() - startTime < sparkleDuration) {
    int sparkleCount = random(5, 15); // Number of LEDs to sparkle each interval

    for(int i = 0; i < sparkleCount; i++) {
      int x = random(0, kMatrixWidth);
      int y = random(0, kMatrixHeight);
      leds[XY(x, y)] = CHSV(random(0, 256), 255, 255); // Random color
    }

    FastLED.show();
    delay(currentInterval);

    // Gradually increase the interval to slow down sparkles
    if(currentInterval < 200) { // Max interval of 500ms
      currentInterval += 1;
    }
  }

  // Fade Out Phase: Gradually turn off LEDs
  for(int brightness = 255; brightness >= 0; brightness -= 5) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(15); // Fade each LED
    }
    FastLED.show();
    delay(1);
  }

  // Display the dice face smoothly
  displayDiceFace(faceIndex);
}

void setup() {
  // Initialize Serial Communication for Debugging
  Serial.begin(9600);
  Serial.println("=== LED Matrix Dice Display Initialized ===");

  // Initialize FastLED
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialize Button Pin
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  Serial.println("Button pin initialized with INPUT_PULLUP.");

  // Seed the random number generator
  randomSeed(analogRead(A0)); // Use an unconnected analog pin for randomness
  Serial.println("Random seed initialized.");
}

void loop() {
  // Check if the button is pressed (active LOW)
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed!");

    // Simple debounce: wait for 50ms and check again
    delay(50);
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("Button press confirmed.");

      // Select a random dice face (0 to 5)
      int randomFace = random(0, 6);
      Serial.print("Selected Dice Face: ");
      Serial.println(randomFace + 1); // Display 1-6 instead of 0-5

      // Perform sparkle animation and display the selected dice face
      sparkleAndDisplayDice(randomFace);
      Serial.println("Displayed dice face on LED matrix.");


      // Wait until the button is released
      while(digitalRead(BUTTON_PIN) == LOW) {
        delay(10); // Small delay to avoid busy-waiting
      }

      Serial.println("Button released.");
    } else {
      Serial.println("Button press ignored (debounce).");
    }
  }
}