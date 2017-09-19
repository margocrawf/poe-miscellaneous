int buttonInput = 3;
int buttonState = 0;
int prevButtonState = 0;
int lightState = 0;
int redLightOutput = 13;
int yellowLightOutput = 12;
int greenLightOutput = 11;
int blinkSpeed = 1000;
int potPin = 2;
int lastFlashTime = millis();
int flashState = HIGH;


unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

boolean shouldToggle() {
  // determines if should be toggled, based on previous button state
  // and debouncing
  int reading = digitalRead(buttonInput);
  if (reading != prevButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        return true;
      }
    }
  }
  prevButtonState = reading;
  return false;
}

void writeLights(int state) {
  //set lights to high or low depending on the state
  if (state == 0) {
    digitalWrite(redLightOutput, LOW);
    digitalWrite(greenLightOutput, LOW);
    digitalWrite(yellowLightOutput, LOW);
  }
  else if (state == 1) {
    digitalWrite(redLightOutput, HIGH);
    digitalWrite(greenLightOutput, HIGH);
    digitalWrite(yellowLightOutput, HIGH);
  }
  else if (state == 2) {
    if ((millis()-lastFlashTime) > blinkSpeed) {
      flashState = !flashState;
      lastFlashTime = millis();
    }
    digitalWrite(redLightOutput, flashState);
    digitalWrite(greenLightOutput, flashState);
    digitalWrite(yellowLightOutput, flashState);
  }
  else if (state == 3) {
    digitalWrite(redLightOutput, LOW);
    digitalWrite(greenLightOutput, LOW);
    digitalWrite(yellowLightOutput, HIGH);
  }
  else if (state == 4) {
    digitalWrite(redLightOutput, LOW);
    digitalWrite(greenLightOutput, HIGH);
    digitalWrite(yellowLightOutput, LOW);
  }
}

void setup() {
  // digital pin 13 is the light output pin, 3 is the button input
  pinMode(redLightOutput, OUTPUT);
  pinMode(yellowLightOutput, OUTPUT);
  pinMode(greenLightOutput, OUTPUT);
  pinMode(buttonInput, INPUT);
  digitalWrite(buttonInput, HIGH);

}

void loop() {
    //get the value from the pot's analog pin
    int potRead = analogRead(potPin);
    blinkSpeed = 10000/potRead;
    //button being pressed
    if (shouldToggle()) {
      //if the button was just pressed, switch the state
      lightState = (lightState + 1) % 5;
      writeLights(lightState);
    }
   else {
    //don't change the state, just write it
    writeLights(lightState);
  }
}

