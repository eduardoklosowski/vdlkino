/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <Arduino.h>
#include "Vdlkino.h"
#include "VdlkinoSerial.h"

VdlkinoSerial::VdlkinoSerial(uint8_t digital, uint8_t analog,
                             HardwareSerial *serial)
        : Vdlkino(digital, analog) {
    this->serial = serial;
}
