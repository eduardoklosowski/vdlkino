#include "VdlkinoSerial.h"

VdlkinoSerial vdlkino(14, 6, &Serial);

uint16_t get_analog_byte(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  return map(analogRead(vblock->pin), 0, 1023, 0, 255);
}

void setup() {
  Serial.begin(9600);
  vdlkino.operations[8] = &get_analog_byte;
}

void loop() {
  vdlkino.run();
}
