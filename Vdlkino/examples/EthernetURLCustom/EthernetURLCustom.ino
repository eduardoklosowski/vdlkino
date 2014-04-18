/*
    Copyright (c) 2014 Eduardo Augusto Klosowski
    License: MIT (see LICENSE for details)
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Vdlkino.h>
#include <VdlkinoEthernet.h>

class VdlkinoEthernetCustom: public VdlkinoEthernet {
public:
    VdlkinoEthernetCustom(uint8_t digital, uint8_t analog,
        EthernetServer *server) : VdlkinoEthernet(digital, analog, server) {}

    virtual void fromURL(VdlkinoBlock *block, char *url) {
        char buffer[256];
        char *urlp = buffer;

        strcpy(urlp, url);
        if (urlp[0] == '/') {
            urlp++;
        }

        urlp = strtok(urlp, "/");
        if (strcmp(urlp, "ledon") == 0) {
            block->oper = VDLKINO_OPER_SETDIGITAL;
            block->pin = 3;
            block->value = 1;
            block->valid = 1;
            return;
        } else if (strcmp(urlp, "ledoff") == 0) {
            block->oper = VDLKINO_OPER_SETDIGITAL;
            block->pin = 3;
            block->value = 0;
            block->valid = 1;
            return;
        } else {
            VdlkinoEthernet::fromURL(block, url);
            return;
        }
    }
};

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,1,177);
EthernetServer server(80);
VdlkinoEthernetCustom vdlkino(14, 6, &server);

void setup() {
    Ethernet.begin(mac, ip);
    server.begin();
}

void loop() {
    vdlkino.run();
    delay(1000);
}
