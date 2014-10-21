/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#ifndef vdlkino_h
#define vdlkino_h

#define VDLKINO_AUTO 3
#define VDLKINO_ERROR 0x8000

#include <Arduino.h>


class Vdlkino;
class VdlkinoBlock;


class Vdlkino {
public:
    uint8_t digital;
    uint8_t analog;
    boolean *pin_auto;
    uint8_t *pin_mode;
    uint16_t (*operations[256]) (void*);

    Vdlkino(uint8_t digital, uint8_t analog);
    ~Vdlkino();
    virtual VdlkinoBlock getBlock();
    virtual void replay(uint16_t value);
    virtual void run();
};


class VdlkinoBlock {
public:
    Vdlkino *vdlkino;
    boolean valid;
    uint8_t oper;
    uint8_t pin;
    uint16_t value;

    VdlkinoBlock(Vdlkino *vdlkino);
    uint16_t run();
};

#endif
