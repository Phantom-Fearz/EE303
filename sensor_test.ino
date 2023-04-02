int AnalogValue[5] = {0,0,0,0,0};
int AnalogPin[5] = {23, 24, 25, 26, 28};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 5; i++){
    AnalogValue[i] = analogRead(AnalogPin[i]);

 
  }
  Serial.println(AnalogValue[1]);
  
}
