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

VdlkinoBlock VdlkinoSerial::getBlock() {
    VdlkinoBlock block = Vdlkino::getBlock();
    char buffer[5];

    if (this->serial->readBytes(buffer, 5) == 5) {
        block.operh = buffer[0];
        block.operl = buffer[1];
        block.pin = buffer[2];
        block.valueh = buffer[3];
        block.valuel = buffer[4];
        block.valid = 1;
    }
    return block;
}


void VdlkinoSerial::replay(uint16_t value) {
    this->serial->write(value >> 8);
    this->serial->write(value & 0xff);
}

void VdlkinoSerial::run() {
    VdlkinoBlock block = this->getBlock();
    if (block.valid) {
        this->replay(block.run());
    }
}
