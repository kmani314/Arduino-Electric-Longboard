#include <VirtualWire.h>
char joystickSend[4];
bool switchState;
int joystickVal;
void setup() {
  Serial.begin(9600);
  vw_setup(2000);

}

void loop() {

  joystickVal = analogRead(A0);
  joystickVal = map(joystickVal, 969, 31, 0, 255);
  joystickSend[0] = joystickVal;
  Serial.println(joystickSend);
  vw_send((uint8_t *)joystickSend, strlen(joystickSend));
  vw_wait_tx();

}
