#include <Servo.h>

int servoAngle = 0;
const int servoPin = 27, interValMs = 50;
const int buttonPin = 20, ledPin = 21, regularLedPin = 25;

int buttonState = 0;

Servo servo;

void setup() {
  servo.attach(servoPin);
  
  pinMode(ledPin, OUTPUT);   
  pinMode(regularLedPin, OUTPUT);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(regularLedPin, HIGH);
    digitalWrite(ledPin, LOW);
    controlServo();
  } else {
    // turn LED off:
    digitalWrite(regularLedPin, LOW);
    digitalWrite(ledPin, HIGH);
  }
  
}

void controlServo() {  
  if (servoAngle >= 180) {    
    for(;servoAngle = 0; servoAngle--) {
        servo.write(servoAngle);
        delay(10);      
    }
    servoAngle = 0;    
  }
  servoAngle++;
  
  servo.write(servoAngle);
  delay(interValMs);
}
