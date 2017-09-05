int buttonInput = 3;
int buttonState = 0;
int prevButtonState = 0;
int lightState = LOW;
int redLightOutput = 13;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // digital pin 13 is the light output pin, 3 is the button input
  pinMode(redLightOutput, OUTPUT);
  pinMode(buttonInput, INPUT);
  digitalWrite(buttonInput, HIGH);

}

void loop() {
  prevButtonState = buttonState;
  buttonState = digitalRead(buttonInput);
  //button being pressed
  if (buttonState == HIGH) {
    if (prevState != buttonState) {
      //if the button was just pressed, switch the state
      lightState = !lightState;
    }
    digitalWrite(redLightOutput, lightState);
  } else {
    //don't change the state, just write it
    digitalWrite(redLightOutput, lightState);
  }
}

boolean shouldToggle() {
  // determines if should be toggled, based on previous button state
  // and debouncing
  prevButtonState = buttonState;
  int reading = digitalRead(buttonInput);
  if (reading != prevButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;
    if (reading != buttonState) {
      prevButtonState = reading;
      return true;
    }
  }
  prevButtonState = reading;
  return false;
}

