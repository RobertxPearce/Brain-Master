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

// LED and Button Pin Definitions.
const int LED_RED        = 2;
const int LED_GREEN      = 3;
const int LED_BLUE       = 4;
const int LED_YELLOW     = 5;
const int BUTTON_RED     = 6;
const int BUTTON_GREEN   = 7;
const int BUTTON_BLUE    = 8;
const int BUTTON_YELLOW  = 9;

// Buzzer pin definition
const int BUZZER = 11;

// Array Definitions
int ledPins[4] = {LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW};
int buttonPins[4] = {BUTTON_RED, BUTTON_GREEN, BUTTON_BLUE, BUTTON_YELLOW};
int gamePattern[20]; // Stores the sequence of LEDs
int playerInput[20]; // Stores the player's sequence

// Game Variables
int gameLength = 5; // current length of the game sequence

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
    Serial.begin(9600);
    for (int i = 0; i < 4; i++) {       // Initialize all LED and button pins.
        pinMode(ledPins[i], OUTPUT);    // Initialize LED pins to output.
        pinMode(buttonPins[i], INPUT);  // Initialize button pins to input.
        //pinMode(buttonPins[i], INPUT_PULLUP);
    }
    startGame();                        // Call start game indicator
}

///-------------------------------------------

void loop() {
    int maxRounds = 4;                                  // Max amount of rounds.
    gameLength = 1;                                     // Game length (leds lit up).
    createPattern();                                    // Call to function to create pattern.

    for (int round = 1; round <= maxRounds; round++) {  // For loop controlled by max rounds.
        Serial.print("Round: ");                        // Print round number.
        Serial.println(round);
        playSequence();                                 // Display the sequence to the player.
        if (!readPlayerInput()) {                       // Check player input against the sequence.
            Serial.println("Game Over!");               // Print game over if incorrect.
            gameOver();                                 // Call to function to print game over sequence.
            break;                                      // Stop the game.
        }
        Serial.println("Correct!");                     // Print player won.
        if (round < maxRounds) {                        // Check if max round was reached.
            gameLength++;                               // If not increment game lenght (amt of LEDs lit up).
            createPattern();                            // Call to function to create new pattern.
        } else {                                        // Else if max rounds has been reached.
            gameWon();                                  // Call to function to print game won sequence.
            break;                                      // Stop the game after winning.
        }
    }
    delay(5000);                                        // Delay before restarting game.
    setup();                                            // Restart the game.
}

///-------------------------------------------
///         FUNCTION DEFINITIONS
///-------------------------------------------

void startGame() {
    Serial.println("Get ready to play!");   // Print message to alert game will start.
    for (int i = 0; i < 4; i++) {           // for Loop to light LEDs up.
        digitalWrite(ledPins[i], HIGH);     // Set LED pin at index to high.
        delay(1000);                        // Delay for 1 second.
        digitalWrite(ledPins[i], LOW);      // Set LED pin at index to low.
    }
    playTone(NOTE_C5, 1000);                // Play tone for one second.
}

///-------------------------------------------

void gameOver() {
    for (int i = 0; i < 4; i++) {         // Flash all LEDs to indicate game over.
        digitalWrite(ledPins[i], HIGH);   // Set pin at index to high.
        playTone(NOTE_A4, 1000);          // Play tone.
        delay(1000);                      // Delay for 1 second. 
        digitalWrite(ledPins[i], LOW);    // Set pin at index to low.
    }
}

///-------------------------------------------

void gameWon() {
    Serial.println("You've won the game!");   // Print that the player has won.
    for (int i = 0; i < 4; i++) {             // Flash LEDs in a celebratory pattern
        digitalWrite(ledPins[i], HIGH);       // Turn LED at index on.
        delay(1000);                          // Delay for 1 second.
        digitalWrite(ledPins[i], LOW);        // Turn LED at index off.
        delay(1000);                          // Delay for 1 second.
    }
    playTone(NOTE_C5, 500);                   // Play note C5.
    playTone(NOTE_D4, 500);                   // Play note D4.
    playTone(NOTE_E4, 500);                   // Play note E4.
}

///-------------------------------------------

void playTone(int note, int duration) {
    tone(BUZZER, note, duration);
    delay(duration + 50);
}

///-------------------------------------------

void createPattern() {
  randomSeed(analogRead(1));              // Set random seed.
  for (int i = 0; i < gameLength; i++) {  // For loop based on game length variable.
    gamePattern[i] = random(1, 5);        // Set index to random LED pin (2-5).
  }
}

///-------------------------------------------

void playSequence() {
    for (int i = 0; i < gameLength; i++) {                    // For loop to iterate based on game length.
        digitalWrite(ledPins[gamePattern[i] - 1], HIGH);      // Turn on LED.
        playTone(NOTE_D4 + (gamePattern[i] - 1) * 100, 700);  // Play a tone.
        delay(800); // Longer delay between flashes           // Delay 
        digitalWrite(ledPins[gamePattern[i] - 1], LOW);       // Turn off LED.
        delay(500);                                           // Delay between LED flashes.
    }
}

///-------------------------------------------

bool readPlayerInput() {
    int inputIndex = 0;                                         // Variable to track index of input.

    while (inputIndex < gameLength) {                           // Loop while input index is less than game length.
        for (int j = 0; j < 4; j++) {                           // For loop to iterate through button array.
            if (digitalRead(buttonPins[j]) == LOW) {            // Check if button was pressed.
                delay(10);                                      // Debounce delay
                if (digitalRead(buttonPins[j]) == LOW) {        // Confirm button press
                    //digitalWrite(ledPins[j], LOW);            // Feedback: Turn on LED
                    //playTone(NOTE_D4 + j * 100, 300);         // Feedback: Play a tone

                    if (j + 1 != gamePattern[inputIndex]) {     // Check if the pressed button matches the game pattern       
                        //digitalWrite(ledPins[j], HIGH);       // Turn off LED
                        return false; // Incorrect input
                    }
                    // Correct button press, move to next input
                    inputIndex++;                               // Go to next input index.
                    while (digitalRead(buttonPins[j]) == LOW);  // Wait for button release
                    //digitalWrite(ledPins[j], HIGH);           // Turn off LED
                    delay(300);                                 // Next input delay
                }
            }
        }
    }
    return true;                                                // Correct input for full sequence
}

///-------------------------------------------
///               END OF FILE
///-------------------------------------------