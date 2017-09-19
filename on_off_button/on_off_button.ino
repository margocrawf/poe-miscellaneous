int buttonInput = 3;
int lightOutput = 13;
int buttonState = 0;
int lightState = LOW;

void setup() {
  // digital pin 13 is the light output pin, 3 is the button input
  pinMode(lightOutput, OUTPUT);
  pinMode(buttonInput, INPUT);
  digitalWrite(buttonInput, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  int prevState = buttonState;
  buttonState = digitalRead(buttonInput);
  //button being pressed
  if (buttonState == HIGH) {
    if (prevState != buttonState) {
      lightState = !lightState;
    }
    digitalWrite(lightOutput, lightState);
  } else {
    //don't change the state, just write it
//    lightState = LOW;
    digitalWrite(lightOutput, lightState);
  }
}
