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

VdlkinoBlock VdlkinoEthernet::getBlock() {
    VdlkinoBlock block = Vdlkino::getBlock();
    EthernetClient client = this->server->available();
    this->client = &client;
    if (client) {
        char buffer[256];
        char *url;
        int i = 0;
        boolean currentLineIsBlank = 1;
        boolean firstline = 1;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (firstline && c != '\n' && c != '\r') {
                    buffer[i] = c;
                    i++;
                    continue;
                }
                if (c == '\n' && currentLineIsBlank) {
                    char *pc;
                    buffer[i] = '\0';
                    pc = strtok(buffer, " ");
                    url = strtok(NULL, " ");
                    break;
                }
                if (c == '\n') {
                    firstline = 0;
                    currentLineIsBlank = 1;
                } else if (c != '\r') {
                    currentLineIsBlank = 0;
                }
            }
        }
        if (url[0] == '/') {
            url++;
        }
        url = strtok(url, "/");
        if (strcmp(url, "raw") == 0) {
            url = strtok(NULL, "/");
            if (url != NULL) {
                block.oper = atoi(url);
            } else {
                return block;
            }
            url = strtok(NULL, "/");
            if (url != NULL) {
                block.pin = atoi(url);
            } else {
                return block;
            }
            url = strtok(NULL, "/");
            if (url != NULL) {
                block.value = atoi(url);
            } else {
                return block;
            }
            block.valid = 1;
        }
    }
    return block;
}

void VdlkinoEthernet::replay(uint16_t value) {
    if (this->client->connected()) {
        this->client->print("HTTP/1.1 ");
        if (!(value & 0x8000)) {
            this->client->println("200 OK");
        } else {
            this->client->println("406 Not Acceptable");
        }
        this->client->println("Content-Type: text/plain");
        this->client->println("Connection: close");
        this->client->println();
        this->client->print(value);
    }
}

void VdlkinoEthernet::run() {
    VdlkinoBlock block = this->getBlock();
    if (block.valid) {
        this->replay(block.run());
    } else {
        this->replay(0x8000);
    }
    this->client->stop();
}
