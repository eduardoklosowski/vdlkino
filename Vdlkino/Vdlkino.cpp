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
    this->oper_custom = NULL;
}

Vdlkino::~Vdlkino() {
    free(this->pin_auto);
    free(this->pin_mode);
}

VdlkinoBlock Vdlkino::getBlock() {
    VdlkinoBlock block(this);
    return block;
}

void Vdlkino::reply(uint16_t value) {
    return;
}

void Vdlkino::run() {
    return;
}

void Vdlkino::addOperCustom(VdlkinoOperCustom *oper_custom) {
    if (this->oper_custom == NULL) {
        this->oper_custom = oper_custom;
        return;
    }
    VdlkinoOperCustom *custom = this->oper_custom;
    while (custom->next != NULL) {
        custom = custom->next;
    }
    custom->next = oper_custom;
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
        case 0x0003:
            return this->getPinMode();
        case 0x0004:
            return this->setDigital();
        case 0x0005:
            return this->getDigital();
        case 0x0006:
            return this->setAnalog();
        case 0x0007:
            return this->getAnalog();
        default:
            VdlkinoOperCustom *custom = this->vdlkino->oper_custom;
            while (custom != NULL) {
                if (custom->oper == this->oper) {
                    return custom->run(this);
                }
                custom = custom->next;
            }
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

uint16_t VdlkinoBlock::getPinMode() {
    if (!this->checkDigitalPin()) {
        return 0x8003;
    }
    if (this->vdlkino->pin_auto[this->pin]) {
        return VDLKINO_AUTO;
    }
    return this->vdlkino->pin_mode[this->pin];
}

uint16_t VdlkinoBlock::setDigital() {
    if (!this->checkDigitalPin()) {
        return 0x8003;
    }
    if (this->vdlkino->pin_mode[this->pin] != OUTPUT) {
        if (this->vdlkino->pin_auto[this->pin]) {
            this->vdlkino->pin_mode[this->pin] = OUTPUT;
            pinMode(this->pin, OUTPUT);
        }
    }
    digitalWrite(this->pin, this->value);
    return 0x0000;
}

uint16_t VdlkinoBlock::getDigital() {
    if (!this->checkDigitalPin()) {
        return 0x8003;
    }
    if (this->vdlkino->pin_mode[this->pin] != INPUT) {
        if (this->vdlkino->pin_auto[this->pin]) {
            this->vdlkino->pin_mode[this->pin] = INPUT;
            pinMode(this->pin, INPUT);
        }
    }
    return digitalRead(this->pin);
}

uint16_t VdlkinoBlock::setAnalog() {
    if (!this->checkDigitalPin()) {
        return 0x8003;
    }
    analogWrite(this->pin, this->value);
    return 0x0000;
}

uint16_t VdlkinoBlock::getAnalog() {
    if (!this->checkAnalogPin()) {
        return 0x8003;
    }
    return analogRead(this->pin);
}

VdlkinoOperCustom::VdlkinoOperCustom(uint16_t oper,
                                     uint16_t (*run)(VdlkinoBlock*)) {
    this->oper = oper;
    this->run = run;
    this->next = NULL;
}
