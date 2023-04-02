/////////////////// Pin Definitions /////////////////////////
int motor1PWM = 39; // P2.6
int motor1Phase = 40; // P2.7
int motor2PWM = 34; //P2.3
int motor2Phase = 38; //P2.4
int AnalogValue[5] = {0, 0, 0, 0, 0};
int AnalogPin[5] = {23, 24, 25, 26, 28};
int distanceSensor = 30;
///////////////// Global Variables ///////////////////////////
int distance = 0;
int count = 0;
int complete = 0;
int wall = 0;
int destination;
int current;
unsigned long timep = 0;
const long interval = 50;
unsigned long sensorDelay = 0;
///////////////////// Sensor Methods ///////////////////////
void sendPosition(int position);

void readDistance() {
  distance = analogRead(distanceSensor);
}

void readSensor() {
  for (int i = 0; i < 5; i++) {
    AnalogValue[i] = analogRead(AnalogPin[i]);
    //delay(200);
  }

}

void countIncrement() {
  if (AnalogValue[0] < 500 && AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500 && AnalogValue[4] < 500 ) {
    count++;
    Serial.println(count);
  }
}
///////////////// Drive Method /////////////////////////
void move() {

  for (int i = 0; i < 5; i++) {
    AnalogValue[i] = analogRead(AnalogPin[i]);
    //delay(200);
  }

  //FAR RIGHT
  if ((AnalogValue[4] < 500 && AnalogValue[3] < 500 && AnalogValue[2] > 500) || (AnalogValue[2] > 500 && AnalogValue[3] > 500 && AnalogValue[4] < 500)) {
    digitalWrite(motor1Phase, HIGH); //right
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 65); // set speed of motor
    analogWrite(motor2PWM, 0);
  }

  // RIGHT
  if ( (AnalogValue[1] > 500 /*&& AnalogValue[4] > 500*/ && AnalogValue[2] < 500 && AnalogValue[3] < 500) || (AnalogValue[1] > 500 && AnalogValue[2] > 500 && AnalogValue[3] < 500 /*&& AnalogValue[4] > 500*/)) {
    digitalWrite(motor1Phase, HIGH); //right
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 65); // set speed of motor
    analogWrite(motor2PWM, 0);
  }

  //CENTER
  if ((AnalogValue[1] > 500 && AnalogValue[2] < 500 && AnalogValue[3] > 500) || (AnalogValue[1] < 500 && AnalogValue[2] > 500 && AnalogValue[3] < 500)) {
    digitalWrite(motor1Phase, HIGH); //center
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 65); // set speed of motor
    analogWrite(motor2PWM, 165);
  }

  //TURN LEFT
  if ((AnalogValue[1] < 500 && AnalogValue[2] < 500 &&  AnalogValue[0] > 500 && AnalogValue[3] > 500) || (AnalogValue[1] < 500 && AnalogValue[2] > 500 && AnalogValue[3] > 500)) {
    digitalWrite(motor1Phase, LOW); //left
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 0); // set speed of motor
    analogWrite(motor2PWM, 165);
  }

  //FAR_LEFT
  if ((AnalogValue[0] < 500 && AnalogValue[1] > 500 && AnalogValue[2] > 500) || (AnalogValue[0] < 500 && AnalogValue[1] < 500 && AnalogValue[2] > 500)) {
    digitalWrite(motor1Phase, LOW); //  FAR-LEFT
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 0); // set speed of motor
    analogWrite(motor2PWM, 198);
  }
}
////////////////// 0 --> destination /////////////////////
void route01() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500 ) {
        count++;
        //Serial.println(count);
      }
    }


    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //turn left
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 110);
      delay(500);
      count++;

    }
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(1);

    }
  }

}


void route02() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 2) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(2);
    }
  }

}

void route03() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(3);
    }
  }

}

void route04() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 100);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(4);
    }
    if (count == 2) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }
  }
}
void route05() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //turn left
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 110);
      delay(500);
      count++;

    }
    if (count == 4) {
      digitalWrite(motor1Phase, HIGH); //center
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 110);
      complete = 1;
    }
  }
  Serial.println(complete);
  while (complete == 1) {
    distance = analogRead(distanceSensor);
    Serial.println(distance);
    if (distance > 400) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 2;
      sendPosition(5);
    }
  }

}

/////////////////////// 1 --> Destination /////////////////////
void route10() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1000);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, HIGH); //turn left
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 0);
      delay(500);
      count++;
    }
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(0);
    }
    if (count == 4) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }
  }
}

void route12() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1000);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //turn left
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 110);
      delay(500);
      count++;

    }
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(2);

    }
  }
}
void route13() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1000);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //turn left
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 110);
      delay(500);
      count++;

    }
    if (count == 4) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(3);
    }
  }

}

void route14() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1000);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, HIGH); //turn right
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 0);
      delay(500);
      count++;
    }
    if (count == 4) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(4);
    }
    if (count == 5) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }
  }
}

void route15() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, HIGH); //center
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 110);
      complete = 1;
    }
  }
  Serial.println(complete);
  while (complete == 1) {
    distance = analogRead(distanceSensor);
    Serial.println(distance);
    if (distance > 600) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 2;
      sendPosition(5);
    }
  }
}
/////////////////////////// 2 --> Destination ////////////////////////////////
void route20() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 2) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(0);
    }
    if (count == 3) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }
  }
}
void route21() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, HIGH); //turn right
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 65); // set speed of motor
      analogWrite(motor2PWM, 0);
      delay(500);
      count++;
    }
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(1);
    }
  }
}
void route23() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(3);
    }
  }
}
void route24() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 4) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(4);
    }
  }
}
void route25() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, HIGH); //right
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 65); // set speed of motor
      analogWrite(motor2PWM, 0);
      delay(500);
      count++;
    }
    if (count == 4) {
      digitalWrite(motor1Phase, HIGH); //center
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 110);
      complete = 1;
    }
  }
  while (complete == 1) {
    distance = analogRead(distanceSensor);
    Serial.println(distance);
    if (distance > 600) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      complete = 2;
      sendPosition(5);
    }
  }
}
/////////////////////// 3 --> Destination ///////////////////
void route30() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(0);
    }
  }

}
void route31() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //turn right
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 120);
      delay(500);
      count++;
    }
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(1);
    }
    if (count == 4) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }

  }
}
void route32() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(2);
    }
    if (count == 2) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }
  }
}
void route34() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(4);
    }
  }
}
void route35() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, HIGH); //right
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 65); // set speed of motor
      analogWrite(motor2PWM, 0);
      delay(800);
      complete = 1;
    }
  }
  while (complete == 1) {
    digitalWrite(motor1Phase, HIGH); //center
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 100); // set speed of motor
    analogWrite(motor2PWM, 110);
    distance = analogRead(distanceSensor);
    Serial.println(distance);
    if (distance > 600) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      complete = 2;
      sendPosition(5);
    }
  }
}
///////////////////////////////// 4 --> Destionation //////////////////
void route40() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(0);
    }
  }

}
void route41() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //turn left
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 110);
      delay(500);
      count++;
    }
    if (count == 5) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(1);
    }
  }

}
void route42() {
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 3) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count = 0;
      complete = 1;
      sendPosition(2);
    }
  }

}
void route43() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 2) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      count ++;
      sendPosition(3);
    }
    if (count == 3) {
      digitalWrite(motor1Phase, HIGH); //u-turn
      digitalWrite(motor2Phase, HIGH);
      analogWrite(motor1PWM, 100); // set speed of motor
      analogWrite(motor2PWM, 100);
      delay(800);
      if (AnalogValue[2] < 500) {
        digitalWrite(motor1Phase, LOW); //stop
        digitalWrite(motor2Phase, LOW);
        analogWrite(motor1PWM, 0); // set speed of motor
        analogWrite(motor2PWM, 0);
        count = 0;
        complete = 1;
      }
    }
  }

}
void route45() {
  digitalWrite(motor1Phase, LOW); //u-turn
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  delay(1200);
  while (complete == 0) {
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }
    if (millis() >= sensorDelay + interval) {
      sensorDelay += interval;
      if ( AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500) {
        count++;
        //Serial.println(count);
      }
    }
    move();
    if (count == 1) {
      digitalWrite(motor1Phase, LOW); //right
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 165);
      delay(600);
      complete = 1;
    }
  }
  while (complete == 1) {
    digitalWrite(motor1Phase, HIGH); //center
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 100); // set speed of motor
    analogWrite(motor2PWM, 110);
    distance = analogRead(distanceSensor);
    Serial.println(distance);
    if (distance > 600) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      complete = 2;
      sendPosition(5);
    }
  }
}
///////////////////// Parking ///////////////////////
void park() {
  digitalWrite(motor1Phase, HIGH); //center
  digitalWrite(motor2Phase, LOW);
  analogWrite(motor1PWM, 100); // set speed of motor
  analogWrite(motor2PWM, 110);
  while (complete == 0) {
    distance = analogRead(distanceSensor);
    if (distance > 400) {
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      complete = 1;
    }
  }
  sendPosition(5);
}
/////////////////// Start at 0 /////////////////////////
void startPosition() {
  while (count < 2) {
    move();
    for (int i = 0; i < 5; i++) {
      AnalogValue[i] = analogRead(AnalogPin[i]);
      //delay(200);
    }


    if (AnalogValue[0] < 500 && AnalogValue[1] < 500 && AnalogValue[2] < 500 && AnalogValue[3] < 500 && AnalogValue[4] < 500 ) {
      count++;
      Serial.println(count);
    }
  }
  if (count == 2) {
    digitalWrite(motor1Phase, LOW); //stop
    digitalWrite(motor2Phase, LOW);
    analogWrite(motor1PWM, 0); // set speed of motor
    analogWrite(motor2PWM, 0);
    delay(500);
    sendPosition(0);
    count = 0;
  }


}
////////////////////// MAIN ////////////////////////////
void setup() {
  Serial.begin(9600);
  connectToWiFi();
  connect();
  startPosition();


}

void loop() {
  complete = 0;
  count = 0;
  current = destination;
  receiveResponse();
  switch (current) {
    case 0:
      if (destination == 1) {
        route01();
      }
      if (destination == 2) {
        route02();
      }
      if (destination == 3) {
        route03();
      }
      if (destination == 4) {
        route04();
      }
      if (destination == 5) {
        route05();
      }
      break;
    case 1:
      if (destination == 0) {
        route10();
      }
      if (destination == 2) {
        route12();
      }
      if (destination == 3) {
        route13();
      }
      if (destination == 4) {
        route14();
      }
      if (destination == 5) {
        route15();
      }
      break;
    case 2:
      if (destination == 0) {
        route20();
      }
      if (destination == 1) {
        route21();
      }
      if (destination == 3) {
        route23();
      }
      if (destination == 4) {
        route24();
      }
      if (destination == 5) {
        route25();
      }
      break;
    case 3:
      if (destination == 0) {
        route30();
      }
      if (destination == 1) {
        route31();
      }
      if (destination == 2) {
        route32();
      }
      if (destination == 4) {
        route34();
      }
      if (destination == 5) {
        route35();
      }
      break;
    case 4:
      if (destination == 0) {
        route40();
      }
      if (destination == 1) {
        route41();
      }
      if (destination == 2) {
        route42();
      }
      if (destination == 3) {
        route43();
      }
      if (destination == 5) {
        route45();
      }
      break;
    default:
      digitalWrite(motor1Phase, LOW); //stop
      digitalWrite(motor2Phase, LOW);
      analogWrite(motor1PWM, 0); // set speed of motor
      analogWrite(motor2PWM, 0);
      break;

  }

}
