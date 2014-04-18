/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <Vdlkino.h>
#include <VdlkinoSerial.h>

VdlkinoSerial vdlkino(14, 6, &Serial);

void setup() {
    Serial.begin(9600);
}

void loop() {
    vdlkino.run();
}
