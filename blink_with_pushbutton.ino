const int buttonPin = 20, ledPin = 21, regularLedPin = 25;

int buttonState = 0;
void setup() {
  
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
  } else {
    // turn LED off:
    digitalWrite(regularLedPin, LOW);
    digitalWrite(ledPin, HIGH);
  }
}
