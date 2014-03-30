/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Vdlkino.h>
#include <VdlkinoEthernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,1,177);
EthernetServer server(80);
VdlkinoEthernet vdlkino(14, 6, &server);

uint16_t testOper(VdlkinoBlock *block) {
    return map(block->getAnalog(), 0, 1023, 0, 255);
}

VdlkinoOperCustom custom = VdlkinoOperCustom(0x0100, testOper);

void setup() {
    Ethernet.begin(mac, ip);
    server.begin();
    vdlkino.addOperCustom(&custom);
}

void loop() {
    vdlkino.run();
    delay(1000);
}
