/*
 * For getting the average of some sensor vals at a given distance,
 * to plug into a linear regression etc.
 */
const int analogInPin = A0; //pin for the sensor

int sensorValue = 0;

float dist(int sensorVal) {
    return -0.1213*sensorVal + 81.02;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int total = 0;
  for (int i = 0; i < 20; i++) {
    int sensorIn = analogRead(analogInPin);
    total += sensorIn;
    delay(100);
  }
  int avg = total/20;
  Serial.print("sensorval = ");
  Serial.println(avg);
  Serial.print("distance = ");
  Serial.println(dist(avg));
  delay(5000);
}
