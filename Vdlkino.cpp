/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#include "Vdlkino.h"

#ifndef VDLKINO_NOT_DEFAULTS_OPERS
#include "VdlkinoDefault.h"
#endif


/* Vdlkino */

Vdlkino::Vdlkino(uint8_t digital, uint8_t analog) {
  this->digital = digital;
  this->analog = analog;
  this->pin_auto = (boolean*) calloc(this->digital, sizeof(boolean));
  this->pin_mode = (uint8_t*) calloc(this->digital, sizeof(uint8_t));
  for (int i = 0; i < this->digital; i++) {
    this->pin_auto[i] = 1;
  }
  #ifndef VDLKINO_NOT_DEAFULTS_OPERS
  this->operations[0] = &oper_digitalpins;
  this->operations[1] = &oper_analogpins;
  this->operations[2] = &oper_setpinmode;
  this->operations[3] = &oper_getpinmode;
  this->operations[4] = &oper_setdigital;
  this->operations[5] = &oper_getdigital;
  this->operations[6] = &oper_setanalog;
  this->operations[7] = &oper_getanalog;
  #endif
}

Vdlkino::~Vdlkino() {
  free(this->pin_auto);
  free(this->pin_mode);
}

VdlkinoBlock Vdlkino::getBlock() {
  VdlkinoBlock block(this);
  return block;
}

void Vdlkino::replay(uint16_t value) {}

void Vdlkino::run() {}


/* VdlkinoBlock */

VdlkinoBlock::VdlkinoBlock(Vdlkino *vdlkino) {
  this->vdlkino = vdlkino;
  this->valid = 0;
}

uint16_t VdlkinoBlock::run() {
  return this->vdlkino->operations[this->oper](this);
}
