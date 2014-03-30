/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#ifndef vdlkino_h
#define vdlkino_h

#include <Arduino.h>
#include <inttypes.h>

class Vdlkino;
class VdlkinoBlock;

class Vdlkino {
public:
    uint8_t digital;
    uint8_t analog;
    uint8_t *pin_mode;
    uint8_t *pin_auto;
    Vdlkino(uint8_t digital, uint8_t analog);
    ~Vdlkino();
};

class VdlkinoBlock {
public:
    Vdlkino *vdlkino;
    boolean valid;
    union {
        uint16_t oper;
        struct {
            uint8_t operl;
            uint8_t operh;
        };
    };
    uint8_t pin;
    union {
        uint16_t value;
        struct {
            uint8_t valuel;
            uint8_t valueh;
        };
    };
    VdlkinoBlock(Vdlkino *vdlkino);
    uint16_t run();
    uint16_t digitalPins();
    uint16_t analogPins();
};

#endif
