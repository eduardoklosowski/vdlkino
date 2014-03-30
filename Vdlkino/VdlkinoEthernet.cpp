/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <Arduino.h>
#include "Vdlkino.h"
#include "VdlkinoEthernet.h"

VdlkinoEthernet::VdlkinoEthernet(uint8_t digital, uint8_t analog,
                                 EthernetServer *server)
        : Vdlkino(digital, analog) {
    this->server = server;
}
