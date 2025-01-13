#include <ServoEasing.hpp> // Correct header file
#include <Adafruit_NeoPixel.h>
#include <stdlib.h> // For random movements

// Servo Pins
const int neckTiltPin = 9;
const int neckRotatePin = 10;
const int beakPin = 11;

// ServoEasing Objects
ServoEasing neckTilt;
ServoEasing neckRotate;
ServoEasing beak;

// LED Configuration
#define LED1_PIN 6 // Pin for LED 1
#define LED2_PIN 7 // Pin for LED 2
#define NUM_LEDS 1 // Each LED is treated as a single NeoPixel

// NeoPixel Objects
Adafruit_NeoPixel led1(NUM_LEDS, LED1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led2(NUM_LEDS, LED2_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Attach ServoEasing servos
  neckTilt.attach(neckTiltPin);
  neckRotate.attach(neckRotatePin);
  beak.attach(beakPin);

  // Set initial servo positions
  neckTilt.startEaseTo(150, 2000); // Neutral tilt with easing
  neckRotate.startEaseTo(90, 2000); // Neutral rotate with easing
  beak.write(90); // Neutral beak (no easing for now)

  // Initialize RGB LEDs
  led1.begin();
  led2.begin();
  led1.show(); // Initialize LED 1 to 'off'
  led2.show(); // Initialize LED 2 to 'off'

  // Seed the random generator
  randomSeed(analogRead(0));
}

void loop() {
  // Perform Idle Movements
  idleNeckTilt();
  idleNeckRotate();
  beakMovement();
  randomEyeBlink();
}

// Neck Tilt Movement: Slow Bobbing Above 150
void idleNeckTilt() {
  int tiltAngle = random(150, 170); // Random tilt between 150 and 170
  neckTilt.startEaseTo(tiltAngle, 2000); // Smooth movement over 2 seconds
  while (isOneServoMoving()) { // Check if any servo is still moving
    updateAllServos(); // Update servos smoothly
  }
  delay(random(2000, 4000)); // Random delay for natural movement
}

// Neck Rotation: Random Back and Forth
void idleNeckRotate() {
  int rotateAngle = random(45, 135); // Random rotation between 45 and 135
  neckRotate.startEaseTo(rotateAngle, 3000); // Smooth movement over 3 seconds
  while (isOneServoMoving()) { // Check if any servo is still moving
    updateAllServos(); // Update servos smoothly
  }
  delay(random(1000, 3000)); // Random delay for variety
}

// Beak Movements: Two Types
void beakMovement() {
  // Randomly choose one of two movements
  int choice = random(1, 3); // Generates 1 or 2
  if (choice == 1) {
    // Quick peck movement
    beak.write(60); // Open slightly
    delay(300);
    beak.write(135); // Close
    delay(300);
  } else {
    // Wide open and close
    beak.write(45); // Open wide
    delay(500);
    beak.write(135); // Close slowly
    delay(500);
  }
}

// Random Eye Blink
void randomEyeBlink() {
  if (random(0, 10) < 2) { // 20% chance to blink
    // Turn off LEDs briefly
    led1.setPixelColor(0, led1.Color(0, 0, 0)); // LED 1 off
    led2.setPixelColor(0, led2.Color(0, 0, 0)); // LED 2 off
    led1.show();
    led2.show();
    delay(200); // Blink duration
    // Restore greenish-blue color
    led1.setPixelColor(0, led1.Color(0, 255, 128)); // LED 1: Greenish-Blue
    led2.setPixelColor(0, led2.Color(0, 255, 128)); // LED 2: Greenish-Blue
    led1.show();
    led2.show();
  }
}
