/// Robert Pearce
/// Brain Master Project
/// UNLV Vegas STEM Camp
/// 04/27/2024

///-------------------------------------------
///         VARIABLE DECLARATIONS
///-------------------------------------------

// Define buzzer notes.
const int NOTE_D4 = 294;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_G4 = 392;
const int NOTE_A4 = 440;
const int NOTE_C5 = 523;

// LED and Button Pin Definitions for UNO.
// const int LED_RED        = 2;
// const int LED_GREEN      = 3;
// const int LED_BLUE       = 4;
// const int LED_YELLOW     = 5;
// const int BUTTON_RED     = 6;
// const int BUTTON_GREEN   = 7;
// const int BUTTON_BLUE    = 8;
// const int BUTTON_YELLOW  = 9;

// LED and Button Pin Definitions for FireBeetle ESP32.
const int LED_RED        = 2;
const int LED_GREEN      = 13;
const int LED_BLUE       = 14;
const int LED_YELLOW     = 0;
const int BUTTON_RED     = 12;
const int BUTTON_GREEN   = 4;
const int BUTTON_BLUE    = 16;
const int BUTTON_YELLOW  = 17;

// Buzzer pin definition for UNO.
// const int BUZZER = 11;

// Buzzer pin definition for FireBeetle ESP32.
const int BUZZER = 25;

// Array Definitions
int ledPins[4] = {LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW};                  // Array to hold all the LED pin numbers.
int buttonPins[4] = {BUTTON_RED, BUTTON_GREEN, BUTTON_BLUE, BUTTON_YELLOW};   // Array to hold all the button pin numbers.
int gamePattern[20];                                                          // Stores the sequence of LEDs.
int playerInput[20];                                                          // Stores the player's sequence.

// Game Variables
int gameLength = 5; // current length of the game patter (# of LEDs lit up).

///-------------------------------------------
///         FUNCTION PROTOTYPES
///-------------------------------------------

void startGame();                         // Function to que start of game.
void gameOver();                          // Function to show end of game.
void gameWon();                           // Function to show game has been won.
void playTone(int note, int duration);    // Function to play given tone.
void createPattern();                     // Function to create pattern.
bool readPlayerInput();                   // Function to read player input.
void playTone(int note, int duration);    // Function to play tone.
void playSequence();                      // Function to play pattern.

///-------------------------------------------
///               ENTRY POINT
///-------------------------------------------

void setup() {
  Serial.begin(9600);                         // Set serial to 9600.
  for (int i = 0; i < 4; i++) {               // For loop to iterate through pin arrays.
      pinMode(ledPins[i], OUTPUT);            // Initialize LED pins to output.
      pinMode(buttonPins[i], INPUT_PULLUP);   // Initialize button pins to input.
  }
  startGame();                                // Call to start game function to que start.
}

///-------------------------------------------

void loop() {
  int maxRounds = 3;                                    // Number of rounds per game.
  gameLength = 1;                                       // Intial pattern will have 1 LED lit up.
  createPattern();                                      // Generate the first pattern.

  for (int round = 1; round <= maxRounds; round++) {    // For loop to iterate until max round amt it met.
    Serial.print("Round ");                             // Print round lable.
    Serial.println(round);                              // Print round number.
    playSequence();                                     // Display the pattern on LEDs.
    if (!readPlayerInput()) {                           // Check player input against the pattern.
      Serial.println("Game Over!");                     // If doesnt match print game over.
      gameOver();                                       // Call to function to display game over scene.
      break;                                            // Break out of loop and stop game.
    }
    Serial.println("Correct!");                         // If matches print correct.
    if (round < maxRounds) {                            // Check if max rounds has been met.
      gameLength++;                                     // If not increase amount of LEDs lit up.
      createPattern();                                  // Create a new pattern for the next round.
    } else {                                            // If max round has been met.
      gameWon();                                        // Indicate winning the game.
      break;                                            // Stop the game after winning.
    }
  }
  delay(5000);                                          // Wait 5 seconds before restarting.
  setup();                                              // Restart the game.
}

///-------------------------------------------
///         FUNCTION DEFINITIONS
///-------------------------------------------

void startGame() {
  Serial.println("Get ready!");       // Print message to let user know game is starting.
  for (int i = 0; i < 4; i++) {       // For loop to iterate through led array.
    digitalWrite(ledPins[i], LOW);    // Set LED pins to low.
    delay(250);                       // Delay
    playTone(NOTE_C5, 250);           // Play starting tone.
    digitalWrite(ledPins[i], HIGH);   // Set LED pins to high.
  }
  delay(500);                         // Delay before start.
}

///-------------------------------------------

void gameOver() {
  for (int i = 0; i < 4; i++) {       // For loop to iterate through LED array.
    digitalWrite(ledPins[i], LOW);    // Flash all LEDs to indicate game over
  }
  playTone(NOTE_A4, 200);             // Play note A4.
  playTone(NOTE_G4, 200);             // Play note G4.
  playTone(NOTE_F4, 200);             // Play note F4.
  playTone(NOTE_E4, 200);             // Play note E4.
  playTone(NOTE_D4, 200);             // Play note D4.

  delay(1000);                        // Delay
  for (int i = 0; i < 4; i++) {       // For loop to iterate through LED array.
    digitalWrite(ledPins[i], HIGH);   // Set LED pins to High.
  }
}

///-------------------------------------------

void gameWon() {
  Serial.println("You've won the game!"); // Print that user won the game.
  for (int i = 0; i < 4; i++) {           // Flash LEDs in a celebratory pattern.
    digitalWrite(ledPins[i], LOW);        // Set LED pins to low.
    delay(250);                           // Delay
    digitalWrite(ledPins[i], HIGH);       // Set LED pins to high.
    delay(250);                           // Delay
  }
  playTone(NOTE_C5, 500);                 // Play note C5.
  playTone(NOTE_D4, 500);                 // Play note D4.
  playTone(NOTE_E4, 500);                 // Play note E4.
  playTone(NOTE_C5, 500);                 // Play note C5.
  playTone(NOTE_D4, 500);                 // Play note D4.
  playTone(NOTE_E4, 500);                 // Play note E4.
  playTone(NOTE_C5, 1000);                // Play note C5.
}

///-------------------------------------------

void createPattern() {
  randomSeed(analogRead(1));              // Set random seed.
  for (int i = 0; i < gameLength; i++) {  // For loop based on game length.
    gamePattern[i] = random(1, 5);        // Play random pin number in pattern array.
  }
}

///-------------------------------------------

void playSequence() {
  for (int i = 0; i < gameLength; i++) {                  // For loop based on game lenth.
    digitalWrite(ledPins[gamePattern[i] - 1], LOW);       // Turn on LED.
    playTone(NOTE_D4 + (gamePattern[i] - 1) * 100, 500);  // Play a tone.
    delay(600);                                           // Delay
    digitalWrite(ledPins[gamePattern[i] - 1], HIGH);      // Turn off LED.
    delay(400);                                           // Delay
  }
}

///-------------------------------------------

bool readPlayerInput() {
  int inputIndex = 0;                                // Variable to track input index.

  while (inputIndex < gameLength) {                  // Loop while input index is less than game length.
    for (int j = 0; j < 4; j++) {                    // For loop to iterate through button array.
      if (digitalRead(buttonPins[j]) == LOW) {       // Check if button has been pressed.
        delay(10);                                   // Debounce delay.
        if (digitalRead(buttonPins[j]) == LOW) {     // Confirm button press.
          digitalWrite(ledPins[j], LOW);             // Feedback: Turn on LED.
          playTone(NOTE_D4 + j * 100, 300);          // Feedback: Play a tone.

          // Check if the pressed button matches the game pattern
          if (j + 1 != gamePattern[inputIndex]) {    // Check if button press matches pattern.
            digitalWrite(ledPins[j], HIGH);          // Turn off LED.
            return false;                            // Incorrect input.
          }

          // Correct button press, move to next input
          inputIndex++;                              // Increment input index.
          while (digitalRead(buttonPins[j]) == LOW); // Wait for button release.
          digitalWrite(ledPins[j], HIGH);            // Turn off LED.
          delay(300);                                // Next input delay.
        }
      }
    }
  }
  return true;                                       // Correct input for full sequence.
}

///-------------------------------------------

void playTone(int note, int duration) {
  tone(BUZZER, note, duration);         // Play param note for param duration.
  delay(duration + 50);                 // Delay
}

///-------------------------------------------
///               END OF FILE
///-------------------------------------------
