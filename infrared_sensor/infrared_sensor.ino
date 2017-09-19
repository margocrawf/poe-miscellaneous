
#include <Servo.h>

//servo object to control the servo
Servo myservo;

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int sensorMin = 1023;
int sensorMax = 0;
int pos = 0;

int timeOutput = millis();

/*
 * How far away the sensor is from stuff based on its output,
 * which we got using linear regression.
 */
float dist(int sensorVal) {
  return -0.0397*sensorVal + 28.93;
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  myservo.attach(9);
  //digitalWrite(analogOutPin, LOW);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
      //move the servo
      myservo.write(pos);
      delay(100);
      float total = 0;
      for (int i = 0; i < 10; i++) {
        // read the analog in value:
        int tempSensorValue = analogRead(analogInPin);
        // map it to a distance
        float distance = dist(sensorValue);
        //add it to the total for averaging purposes
        total += distance;
        sensorValue = tempSensorValue;
        
        // wait 2 milliseconds before the next loop for the analog-to-digital
        // converter to settle after the last reading:
        delay(20);
      }
      //get the average of the 10 readings
      float distAverage = total / 10.0;
      //print to serial
//      Serial.print("sensor = ");
//      Serial.println(sensorValue);
      Serial.print(" distance = ");
      Serial.print(distAverage);
      Serial.print(" angle = ");
      Serial.println(pos);
  }

  for (pos = 180; pos >= 0; pos -= 1) {
      //move the servo
      myservo.write(pos);
      delay(100);
      float total = 0;
      for (int i = 0; i < 10; i++) {
        // read the analog in value:
        int tempSensorValue = analogRead(analogInPin);
        // map it to a distance
        float distance = dist(sensorValue);
        sensorValue = tempSensorValue;

        // wait 2 milliseconds before the next loop for the analog-to-digital
        // converter to settle after the last reading:
        delay(2);
      }
      //get the average of the 10 readings
      float distAverage = total / 10.0;
      // print the results to the Serial Monitor:
      Serial.print("sensor = ");
      Serial.print(sensorValue);
      Serial.print("distance = ");
      Serial.print(distAverage);
      Serial.print("Angle = ");
      Serial.println(pos);
  }

}
