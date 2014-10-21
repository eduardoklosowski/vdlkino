/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#include "Vdlkino.h"
#include "VdlkinoSerial.h"


/* VdlkinoSerial */

VdlkinoSerial::VdlkinoSerial(uint8_t digital, uint8_t analog, HardwareSerial *serial) : Vdlkino(digital, analog) {
  this->serial = serial;
}

VdlkinoBlock VdlkinoSerial::getBlock() {
  VdlkinoBlock block(this);
  char buffer[4];
  if (this->serial->readBytes(buffer, 4) == 4) {
    block.oper = buffer[0];
    block.pin = buffer[1];
    block.value = buffer[2] << 8 | buffer[3];
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
