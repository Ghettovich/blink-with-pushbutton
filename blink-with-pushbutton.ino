#include <Servo.h>

Servo servo;
int servoAngle = 89;
const int servoPin = 39, interValMs = 10;

// Button clockwise
const int buttonPinClockwise = 19, ledPinButtonClockwise = 29;

// Button counter clockwise
const int buttonPinCounterClockwise = 18, ledPinButtonCounterClockwise = 31;

// indicator LEDs
const int ledMaxRotation = 23;

// Button states
int buttonStateClockwise = 0, buttonStateCounterClock = 0;
int lastButtonStateClockwise = LOW, lastButtonStateCounterClock = LOW;
bool flipServoRotation = false;

// HC SR04 sonar
const int trigPin = 14, echoPin = 15;
long duration;
int distance;

// Timing
const int INTERVAL = 60;
long currentMillis = 0, previousMillis = 0;

// Setup
void setup() {
  Serial.begin(9600);

  // Servo
  servo.attach(servoPin);
  servo.write(servoAngle);

  // initialize the LED pin as an output:
  pinMode(ledMaxRotation, OUTPUT);
  pinMode(ledPinButtonClockwise, OUTPUT);
  pinMode(ledPinButtonCounterClockwise, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPinCounterClockwise, INPUT);
  pinMode(buttonPinClockwise, INPUT);

  // Define inputs and outputs for sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  // read the state of the pushbutton value:
  int reading = digitalRead(buttonPinClockwise);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (reading == HIGH) {
    // turn LED on:
    digitalWrite(ledPinButtonCounterClockwise, LOW);
    digitalWrite(ledPinButtonClockwise, LOW);
    turnServoClockwise();
    Serial.println("Button clockwise pressed");
  } else {
    // turn LED off:
    digitalWrite(ledPinButtonClockwise, HIGH);
  }

  reading = digitalRead(buttonPinCounterClockwise);

  if (reading == HIGH) {
    digitalWrite(ledPinButtonClockwise, LOW);
    digitalWrite(ledPinButtonCounterClockwise, LOW);
    turnServoCounterClockwise();
    Serial.println("Button counter clockwise pressed");
  } else {
    // turn LED off:
    digitalWrite(ledPinButtonCounterClockwise, HIGH);
  }



  if (millis() >= previousMillis + INTERVAL) {
    printAndCalculateDistance();
    previousMillis = millis();
  }

  //toggleMaxRotationLED();
}

void turnServoClockwise() {
  if (servoAngle < 180) {
    servoAngle += 4;
    servo.write(servoAngle);
  } else {
    servoAngle = 180;
  }

  delay(interValMs);
}

void turnServoCounterClockwise() {
  if (servoAngle >= 1) {
    servoAngle -= 4;
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

  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance:
  long DistanceCalc; // Calculation variable
  DistanceCalc = ((duration / 2.9) / 2); // Actual calculation in mm

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(DistanceCalc);
  Serial.println(" mm");

  //delay(60);
}
