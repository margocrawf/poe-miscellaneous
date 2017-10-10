// pins:
const int analogInPin = A0;  // Analog input pin 

int sensorValue = 0; // value read from the pot
int threshold = 0;

int TERMINAL_CHAR = 59; //ascii value of ;

int motorSpeed; //speed of the motor

/*
 * Reassign variables if necessary,
 * from a string of the form
 * "variable_name=value;"
 */
void assign_var(String inputString) {
  // first part of string, before equal sign
   char* varName = strtok(inputString.c_str(), "=");
   Serial.println(varName);
   // if you're assigning motorSpeed
   if (strcmp(varName, "motorSpeed") == 0) {
      // get the thing on other side of equal sign
      char* val = strtok(NULL, ";");
      Serial.print("Changing motor speed to ");
      Serial.println(val);
      //assign the value
      motorSpeed = atoi(val);
   }
}

/*
 * Move the motor based on sensor input and
 * whatever else determines it.
 */
void move_motor(int sensorRight, int sensorLeft) {
  return;
}

/*
 * Setup
 */
void setup() {
  // start the serial
  Serial.begin(9600);
  Serial.flush();
}

/*
 * Loop 5evr
 */
void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
  // move the motor
  move_motor(sensorValue);
  // if there's stuff on the serial port
  if (Serial.available() > 0) {
     // read the serial input
     String serialInput = Serial.readString();
     //assign values based on it
     assign_var(serialInput);
     
  }
  Serial.flush();
  delay(100);

}
