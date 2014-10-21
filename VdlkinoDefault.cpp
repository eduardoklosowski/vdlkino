/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#include "Vdlkino.h"
#include "VdlkinoDefault.h"


uint16_t oper_digitalpins(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  return vblock->vdlkino->digital;
}

uint16_t oper_analogpins(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  return vblock->vdlkino->analog;
}


uint16_t oper_setpinmode(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  if (vblock->pin >= vblock->vdlkino->digital) {
    return VDLKINO_ERROR;
  }
  switch (vblock->value) {
    case INPUT:
      vblock->vdlkino->pin_auto[vblock->pin] = 0;
      vblock->vdlkino->pin_mode[vblock->pin] = INPUT;
      pinMode(vblock->pin, INPUT);
      return 0;
    case OUTPUT:
      vblock->vdlkino->pin_auto[vblock->pin] = 0;
      vblock->vdlkino->pin_mode[vblock->pin] = OUTPUT;
      pinMode(vblock->pin, OUTPUT);
      return 0;
    case INPUT_PULLUP:
      vblock->vdlkino->pin_auto[vblock->pin] = 0;
      vblock->vdlkino->pin_mode[vblock->pin] = INPUT_PULLUP;
      pinMode(vblock->pin, INPUT_PULLUP);
      return 0;
    case VDLKINO_AUTO:
      vblock->vdlkino->pin_auto[vblock->pin] = 1;
      vblock->vdlkino->pin_mode[vblock->pin] = INPUT;
      pinMode(vblock->pin, INPUT);
      return 0;
  }
  return VDLKINO_ERROR;
}

uint16_t oper_getpinmode(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  if (vblock->pin >= vblock->vdlkino->digital) {
    return VDLKINO_ERROR;
  }
  if (vblock->vdlkino->pin_auto[vblock->pin]) {
    return VDLKINO_AUTO;
  }
  return vblock->vdlkino->pin_mode[vblock->pin];
}


uint16_t oper_setdigital(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  if (vblock->pin >= vblock->vdlkino->digital) {
    return VDLKINO_ERROR;
  }
  if (vblock->vdlkino->pin_mode[vblock->pin] != OUTPUT) {
    if (vblock->vdlkino->pin_auto[vblock->pin]) {
      vblock->vdlkino->pin_mode[vblock->pin] = OUTPUT;
      pinMode(vblock->pin, OUTPUT);
    }
  }
  digitalWrite(vblock->pin, vblock->value);
  return 0;
}

uint16_t oper_getdigital(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  if (vblock->pin >= vblock->vdlkino->digital) {
    return VDLKINO_ERROR;
  }
  if (vblock->vdlkino->pin_mode[vblock->pin] != INPUT) {
    if (vblock->vdlkino->pin_auto[vblock->pin]) {
      vblock->vdlkino->pin_mode[vblock->pin] = INPUT;
      pinMode(vblock->pin, INPUT);
    }
  }
  return digitalRead(vblock->pin);
}


uint16_t oper_setanalog(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  if (vblock->pin >= vblock->vdlkino->digital) {
    return VDLKINO_ERROR;
  }
  analogWrite(vblock->pin, vblock->value);
  return 0;
}

uint16_t oper_getanalog(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  if (vblock->pin >= vblock->vdlkino->analog) {
    return VDLKINO_ERROR;
  }
  return analogRead(vblock->pin);
}
