/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#ifndef vdlkino_h
#define vdlkino_h

#include <Arduino.h>
#include <inttypes.h>

#define VDLKINO_AUTO 3

#define VDLKINO_OPER_DIGITALPINS 0x0000
#define VDLKINO_OPER_ANALOGPINS 0x0001
#define VDLKINO_OPER_SETPINMODE 0x0002
#define VDLKINO_OPER_GETPINMODE 0x0003
#define VDLKINO_OPER_SETDIGITAL 0x0004
#define VDLKINO_OPER_GETDIGITAL 0x0005
#define VDLKINO_OPER_SETANALOG 0x0006
#define VDLKINO_OPER_GETANALOG 0x0007

class Vdlkino;
class VdlkinoBlock;
class VdlkinoOperCustom;

class Vdlkino {
public:
    uint8_t digital;
    uint8_t analog;
    uint8_t *pin_mode;
    uint8_t *pin_auto;
    VdlkinoOperCustom *oper_custom;
    Vdlkino(uint8_t digital, uint8_t analog);
    ~Vdlkino();
    virtual VdlkinoBlock getBlock();
    virtual void reply(uint16_t value);
    virtual void run();
    virtual void addOperCustom(VdlkinoOperCustom *oper_custom);
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
    boolean checkDigitalPin();
    boolean checkAnalogPin();
    uint16_t run();
    uint16_t digitalPins();
    uint16_t analogPins();
    uint16_t setPinMode();
    uint16_t getPinMode();
    uint16_t setDigital();
    uint16_t getDigital();
    uint16_t setAnalog();
    uint16_t getAnalog();
};

class VdlkinoOperCustom {
public:
    uint16_t oper;
    uint16_t (*run) (VdlkinoBlock*);
    VdlkinoOperCustom *next;
    VdlkinoOperCustom(uint16_t oper, uint16_t (*run)(VdlkinoBlock*));
};

#endif
