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
    strcpy(this->access, "*");
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
        this->fromURL(&block, url);
    }
    return block;
}

void VdlkinoEthernet::fromURL(VdlkinoBlock *block, char *url) {
    char buffer[256];
    char *urlp = buffer;

    strcpy(urlp, url);
    if (urlp[0] == '/') {
        urlp++;
    }

    urlp = strtok(urlp, "/");
    if (strcmp(urlp, "raw") == 0) {
        urlp = strtok(NULL, "/");
        if (urlp != NULL) {
            block->oper = atoi(urlp);
        } else {
            return;
        }
        urlp = strtok(NULL, "/");
        if (urlp != NULL) {
            block->pin = atoi(urlp);
        } else {
            return;
        }
        urlp = strtok(NULL, "/");
        if (urlp != NULL) {
            block->value = atoi(urlp);
        } else {
            return;
        }
        block->valid = 1;
        return;
    }
}

void VdlkinoEthernet::replay(uint16_t value) {
    if (this->client->connected()) {
        this->client->print("HTTP/1.1 ");
        if (!(value & VDLKINO_ERROR)) {
            this->client->println("200 OK");
        } else {
            this->client->println("406 Not Acceptable");
        }
        this->client->println("Content-Type: text/plain");
        this->client->print("Access-Control-Allow-Origin: ");
        this->client->println(this->access);
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
        this->replay(VDLKINO_ERROR_PROTOCOL);
    }
    this->client->stop();
}
