#include <Servo.h>

//servo object to control the servo
Servo zServo;

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int posZinit = 60;
int posZmax = 90;
int posZ = posZinit;

int delta = 2; //how much the angles change by each time

int timeOutput = millis();

/*
 * How far away the sensor is from stuff based on its output,
 * which we got using linear regression.
 */
float dist(int sensorVal) {
//  return -0.0397*sensorVal + 28.93;
    return -0.1213*sensorVal + 81.02;
}

/*
 * Get the average of 10 sensor readings, to account for occasional
 * inconsistencies in readings
 */
float average_distance_val(int reps) {
  float total = 0;
  for (int i = 0; i < reps; i++) {
    // read the analog in value:
    int tempSensorValue = analogRead(analogInPin);
    // map it to a distance
    float distance = dist(sensorValue);
    //add it to the total for averaging purposes
    total += distance;
    sensorValue = tempSensorValue;
    
    // wait 2 milliseconds before the next loop for the analog-to-digital
    // converter to settle after the last reading:
    delay(50);
  }
  return total/reps;
}

char print_string(float dist, int pos_z) {
  Serial.print("distance = ");
  Serial.print(dist);
  Serial.print(" angle1 = ");
  Serial.print(90);
  Serial.print( " angle2 = ");
  Serial.println(pos_z);
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  zServo.attach(10);
  //digitalWrite(analogOutPin, LOW);
}

void loop() {
    for (posZ = posZinit; posZ <= posZmax; posZ += delta) {
        //move the servo
        zServo.write(posZ);
        delay(100);
        //get the average distance from 10 sensor readings
        float distAverage = average_distance_val(5);
        //print to serial
        print_string(distAverage, posZ);
    }
    for (posZ = posZmax; posZ >= posZinit; posZ -= delta) {
        //move the servo
        zServo.write(posZ);
        delay(100);
        //get the average distance from 10 sensor readings
        float distAverage = average_distance_val(5);
        // print the results to the Serial Monitor:
        print_string(distAverage, posZ);
    }
  }
