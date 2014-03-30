/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <Arduino.h>
#include <inttypes.h>
#include "Vdlkino.h"

Vdlkino::Vdlkino(uint8_t digital, uint8_t analog) {
    this->digital = digital;
    this->analog = analog;
    this->pin_mode = (uint8_t*) calloc(this->digital, 8);
    this->pin_auto = (uint8_t*) calloc(this->digital, 8);
    for (int i = 0; i < digital; i++) {
        this->pin_auto[i] = 1;
    }
}

Vdlkino::~Vdlkino() {
    free(this->pin_auto);
    free(this->pin_mode);
}

VdlkinoBlock::VdlkinoBlock(Vdlkino *vdlkino) {
    this->vdlkino = vdlkino;
    this->valid = 0;
}

boolean VdlkinoBlock::checkDigitalPin() {
    return this->pin < this->vdlkino->digital;
}

boolean VdlkinoBlock::checkAnalogPin() {
    return this->pin < this->vdlkino->analog;
}

uint16_t VdlkinoBlock::run() {
    switch (this->oper) {
        case 0x0000:
            return this->digitalPins();
        case 0x0001:
            return this->analogPins();
        case 0x0002:
            return this->setPinMode();
        default:
            return 0x8002;
    }
}

uint16_t VdlkinoBlock::digitalPins() {
    return this->vdlkino->digital;
}

uint16_t VdlkinoBlock::analogPins() {
    return this->vdlkino->analog;
}

uint16_t VdlkinoBlock::setPinMode() {
    if (!this->checkDigitalPin()) {
        return 0x8003;
    }
    switch (this->value) {
        case INPUT:
            this->vdlkino->pin_auto[this->pin] = 0;
            this->vdlkino->pin_mode[this->pin] = INPUT;
            pinMode(this->pin, INPUT);
            return 0x0000;
        case OUTPUT:
            this->vdlkino->pin_auto[this->pin] = 0;
            this->vdlkino->pin_mode[this->pin] = OUTPUT;
            pinMode(this->pin, OUTPUT);
            return 0x0000;
        case INPUT_PULLUP:
            this->vdlkino->pin_auto[this->pin] = 0;
            this->vdlkino->pin_mode[this->pin] = INPUT_PULLUP;
            pinMode(this->pin, INPUT_PULLUP);
            return 0x0000;
        case VDLKINO_AUTO:
            this->vdlkino->pin_auto[this->pin] = 1;
            this->vdlkino->pin_mode[this->pin] = INPUT;
            pinMode(this->pin, INPUT);
            return 0x0000;
        default:
            return 0x8004;
    }
}
