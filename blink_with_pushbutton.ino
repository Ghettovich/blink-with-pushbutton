#include <Servo.h>

Servo servo;
int servoAngle = 90;
const int servoPin = 39, interValMs = 35;

// Button clockwise
const int buttonPinClockwise = 19, ledPinButtonClockwise = 29;

// Button counter clockwise
const int buttonPinCounterClockwise = 18, ledPinButtonCounterClockwise = 31;

// indicator LEDs
const int ledMaxRotation = 23, ledButtonPressed = 25;

// Button states
int buttonStateClockwise = 0, buttonStateCounterClock = 0;
int lastButtonStateClockwise = LOW, lastButtonStateCounterClock = LOW;
bool flipServoRotation = false;

// HC SR04 sonar
const int trigPin = 14, echoPin = 15;
long duration;
int distance;

// Setup
void setup() {
  // Servo
  servo.attach(servoPin);

  // initialize the LED pin as an output:
  pinMode(ledMaxRotation, OUTPUT);
  pinMode(ledButtonPressed, OUTPUT);
  pinMode(ledPinButtonClockwise, OUTPUT);
  pinMode(ledPinButtonCounterClockwise, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPinCounterClockwise, INPUT);
  pinMode(buttonPinClockwise, INPUT);

  // Define inputs and outputs for sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  int reading = digitalRead(buttonPinClockwise);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (reading == HIGH) {
    // turn LED on:
    digitalWrite(ledButtonPressed, HIGH);
    digitalWrite(ledPinButtonCounterClockwise, LOW);
    digitalWrite(ledPinButtonClockwise, LOW);
    turnServoClockwise();
  } else {
    // turn LED off:
    digitalWrite(ledButtonPressed, LOW);
    digitalWrite(ledPinButtonClockwise, HIGH);
  }

  reading = digitalRead(buttonPinCounterClockwise);

  if (reading == HIGH) {
    digitalWrite(ledButtonPressed, HIGH);
    digitalWrite(ledPinButtonClockwise, LOW);
    digitalWrite(ledPinButtonCounterClockwise, LOW);
    turnServoCounterClockwise();
  } else {
    // turn LED off:
    digitalWrite(ledButtonPressed, LOW);
    digitalWrite(ledPinButtonCounterClockwise, HIGH);
  }

  printAndCalculateDistance();
  toggleMaxRotationLED();
}

void turnServoClockwise() {
  if (servoAngle < 180) {
    servoAngle++;
    servo.write(servoAngle);
  } else {
    servoAngle = 180;
  }

  delay(interValMs);
}

void turnServoCounterClockwise() {
  if (servoAngle >= 1) {
    servoAngle--;
    servo.write(servoAngle);
  }
  else {
    servoAngle = 0;
  }

  delay(interValMs);
}

void toggleMaxRotationLED() {
  if (servoAngle == 180 || servoAngle == 0) {
    digitalWrite(ledMaxRotation, HIGH);
  }
  else {
    digitalWrite(ledMaxRotation, LOW);
  }
}

void printAndCalculateDistance() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

  delay(50);
}
