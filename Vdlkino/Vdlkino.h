/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#ifndef vdlkino_h
#define vdlkino_h

#include <Arduino.h>
#include <inttypes.h>

class VdlkinoBlock;

class VdlkinoBlock {
public:
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
    VdlkinoBlock();
};

#endif
