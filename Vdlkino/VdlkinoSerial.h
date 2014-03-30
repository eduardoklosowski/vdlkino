/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#ifndef vdlkinoserial_h
#define vdlkinoserial_h

#include "Vdlkino.h"

class VdlkinoSerial: public Vdlkino {
public:
    HardwareSerial *serial;
    VdlkinoSerial(uint8_t digital, uint8_t analog, HardwareSerial *serial);
    virtual VdlkinoBlock getBlock();
    virtual void replay(uint16_t value);
};

#endif
