
int distance = 0;
unsigned long sensorDelay = 0;
int motor1PWM = 39; // P2.6
int motor1Phase = 40; // P2.7
int motor2PWM = 34; //P2.3
int motor2Phase = 38; //P2.4
int AnalogValue[5] = {0, 0, 0, 0, 0};
int AnalogPin[5] = {23, 24, 25, 26, 28};
int distanceSensor = 30;

void readDistance() {
  if (millis() >= sensorDelay + 100) {
    sensorDelay += 100;
    distance = analogRead(distanceSensor);
    Serial.println(distance);
  }

}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  readDistance();
}
