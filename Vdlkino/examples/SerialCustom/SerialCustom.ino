/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <Vdlkino.h>
#include <VdlkinoSerial.h>

VdlkinoSerial vdlkino(14, 6, &Serial);

uint16_t testOper(VdlkinoBlock *block) {
    return map(block->getAnalog(), 0, 1023, 0, 255);
}

VdlkinoOperCustom custom = VdlkinoOperCustom(0x0100, testOper);

void setup() {
    Serial.begin(9600);
    vdlkino.addOperCustom(&custom);
}

void loop() {
    vdlkino.run();
    delay(1000);
}
