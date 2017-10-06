
#include <Servo.h>

//servo object to control the servo
Servo xServo;
Servo zServo;

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the sensor
// initial, final, and current angles of rotation about x'
int posXinit = 30;
int posXmax = 75;
int posX = posXinit;
// initial, final, and current angles of rotation about z
int posZinit = 54;
int posZmax = 90;
int posZ = posZinit;
// how much the angles change by each time
int delta = 2;

/*
 * How far away the sensor is from stuff based on its output,
 * which we got using linear regression.
 */
float dist(int sensorVal) {
    return -0.1213*sensorVal + 81.02;
}

/*
 * Get the average of given number of sensor readings, to account for 
 * occasional inconsistencies in readings
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
    // wait 50 milliseconds before the next reading, to allow the
    // sensor to regather the value
    delay(50);
  }
  return total/reps;
}

/*
 * print the distance, x angle and z angle to the
 * serial port
 */
char print_string(float dist, int pos_x, int pos_z) {
  Serial.print("distance = ");
  Serial.print(dist);
  Serial.print(" angle1 = ");
  Serial.print(pos_x);
  Serial.print(" angle2 = ");
  Serial.println(pos_z);
}

/*
 * Things to be done when the program is first run
 */
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  xServo.attach(9);
  zServo.attach(10);
  //digitalWrite(analogOutPin, LOW);
}

/*
 * Things to be repeated while the program is running
 * Does all the scanning and prints to the serial
 */
void loop() {
  //iterate up through Z angles
  for (posZ = posZinit; posZ <= posZmax; posZ += 2*delta) {
    //move the servo in the Z direction
    zServo.write(posZ);
    //iterate up through x angles (zig)
    for (posX = posXinit; posX <= posXmax; posX += delta) {
        //move the servo in the X' direction
        xServo.write(posX);
        //delay, so the servo has time to move
        delay(100);
        //get the average distance from 10 sensor readings
        float distAverage = average_distance_val(5);
        // print the results to the Serial Monitor
        print_string(distAverage, posX, posZ);
    }
    //move the servo in the Z direction
    zServo.write(posZ + delta);
    //iterate down through x angles (zag)
    for (posX = posXmax; posX >= posXinit; posX -= delta) {
        //move the servo in the X' direction
        xServo.write(posX);
        //delay, so the servo has time to move
        delay(100);
        //get the average distance from 10 sensor readings
        float distAverage = average_distance_val(5);
        // print the results to the Serial Monitor
        print_string(distAverage, posX, posZ + delta);
    }
  }
}
