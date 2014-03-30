/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#ifndef vdlkinoethernet_h
#define vdlkinoethernet_h

#include <SPI.h>
#include <Ethernet.h>
#include "Vdlkino.h"

class VdlkinoEthernet: public Vdlkino {
public:
    EthernetServer *server;
    EthernetClient *client;
    VdlkinoEthernet(uint8_t digital, uint8_t analog, EthernetServer *server);
    virtual VdlkinoBlock getBlock();
};

#endif
