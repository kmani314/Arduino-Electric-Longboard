
#include <ServoTimer2.h>
#include <VirtualWire.h>
#define BRAKE_VALUE 1200
#define MOTOR_PIN 9
ServoTimer2 motor;
int voltage;
int escVal;
int ctr;
int ctr2;
int previousVal = 1200;
void setup() {
  startup();
  motor.attach(MOTOR_PIN);
  Serial.begin(9600);
  vw_setup(2000);
  vw_rx_start();
}




void loop() {
  voltage = analogRead(A1);
  voltage = map(voltage, 0, 13, 0, 21);
  voltLed(voltage);
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_have_message()) {
    vw_get_message(buf, &buflen);
    escVal = buf[0];
    ctr = 0;
    if (escVal > 120) {
      escVal = map(escVal, 145, 235, 1350, 1800);
      if (previousVal < escVal) {
        previousVal += 15;
      }
      else {
        previousVal = escVal;
      }
      
    }
    else {
      previousVal = BRAKE_VALUE;
    }
     motor.write(previousVal);
      Serial.println(previousVal);

  }
  else {
    ctr = ctr + 1;
    if (ctr >= 4500) {
      motor.write(BRAKE_VALUE);
      Serial.println("lost connection");
    }
  }
}



void startup() {
  int pins;
  int val;
  for (pins = A2; pins < A6; pins++) {
    delay(50);
    for (val = 0; val < 1023; val++) {
      analogWrite(pins, val);
    }

  }
  for (pins = A5; pins > A1; pins--) {
    delay(50);
    for (val = 1023; val > 0; val--) {
      analogWrite(pins, val);
    }
  }
}



void voltLed(int volts) {

  switch (volts) {
    default :
      digitalWrite(A2, 800);
      digitalWrite(A3, 0);
      digitalWrite(A4, 0);
      digitalWrite(A5, 0);
      break;
    case (18) :
      digitalWrite(A2, 800);
      digitalWrite(A3, 250);
      digitalWrite(A4, 0);
      digitalWrite(A5, 0);
      break;
    case (19) :
      digitalWrite(A2, 800);
      digitalWrite(A3, 250);
      digitalWrite(A4, 250);
      digitalWrite(A5, 0);
      break;
    case (20)  :
      digitalWrite(A2, 800);
      digitalWrite(A3, 250);
      digitalWrite(A4, 250);
      digitalWrite(A5, 250);
      break;
    case (21) :
      digitalWrite(A2, 800);
      digitalWrite(A3, 250);
      digitalWrite(A4, 250);
      digitalWrite(A5, 250);
      break;

  }
}


