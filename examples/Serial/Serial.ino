#include "VdlkinoSerial.h"

VdlkinoSerial vdlkino(14, 6, &Serial);

void setup() {
  Serial.begin(9600);
}

void loop() {
  vdlkino.run();
}
