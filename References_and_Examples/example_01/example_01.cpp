// Include libraries
#include <Arduino.h>

// Define GPIO pins for buttons and LEDs
const int buttonPin1 = 12;  // GPIO pin for Button1
const int buttonPin2 = 13;  // GPIO pin for Button2
const int buttonPin3 = 14;  // GPIO pin for Button3
const int buttonPin4 = 15;  // GPIO pin for Button4
const int ledPin1 = 16;     // GPIO pin for LED1
const int ledPin2 = 17;     // GPIO pin for LED2

// Variables to store button states
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set button pins as input
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  // Set LED pins as output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // Read the state of the buttons
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  // Control the LEDs based on button states
  digitalWrite(ledPin1, buttonState1);
  digitalWrite(ledPin2, buttonState3);

  // Print button states to serial monitor
  Serial.print("Button 1: ");
  Serial.println(buttonState1);
  Serial.print("Button 2: ");
  Serial.println(buttonState2);
  Serial.print("Button 3: ");
  Serial.println(buttonState3);
  Serial.print("Button 4: ");
  Serial.println(buttonState4);

  // Add a small delay to avoid bouncing
  delay(50);
}

/*
       ESP32
       -----
       |USB|
    -----------
        | |
        | |
+3.3V---| |--- LED1 Anode
        | |
GPIOxx--| |--- Button1 (Pull-up resistor to GND)
        | |
        | |
GPIOxx--| |--- Button2 (Pull-up resistor to GND)
        | |
GND-----| |--- LED1 Cathode
        | |
GND-----|_|--- Button1 & Button2 (Connected to GND)
        | |
        | |
+3.3V---| |--- LED2 Anode
        | |
GPIOxx--| |--- Button3 (Pull-up resistor to GND)
        | |
GPIOxx--| |--- Button4 (Pull-up resistor to GND)
        | |
GND-----|_|--- LED2 Cathode
        | |
        | |
*/