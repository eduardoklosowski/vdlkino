/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#include "VdlkinoEthernet.h"

#ifndef VDLKINO_NOT_DEFAULTS_URLS
#include "VdlkinoDefaultUrl.h"
#endif


/* VdlkinoEthernet */

VdlkinoEthernet::VdlkinoEthernet(uint8_t digital, uint8_t analog, EthernetServer *server) : Vdlkino(digital, analog) {
  this->server = server;
  strcpy(this->access, "*");
  this->urls = 0;
  #ifndef VDLKINO_NOT_DEFAULTS_URLS
  this->addUrl(&url_raw);
  this->addUrl(&url_digitalpins);
  this->addUrl(&url_analogpins);
  this->addUrl(&url_setpinmode);
  this->addUrl(&url_getpinmode);
  this->addUrl(&url_setdigital);
  this->addUrl(&url_getdigital);
  this->addUrl(&url_setanalog);
  this->addUrl(&url_getanalog);
  #endif
}

void VdlkinoEthernet::addUrl(void (*function) (void*, char*)) {
  VdlkinoEthernetUrl *func = new VdlkinoEthernetUrl(function);
  VdlkinoEthernetUrl *urls = this->urls;
  if (!urls) {
    this->urls = func;
    return;
  }
  while (urls->next) {
    urls = urls->next;
  }
  urls->next = func;
}

VdlkinoBlock VdlkinoEthernet::getBlock() {
  VdlkinoBlock block(this);
  EthernetClient client = this->server->available();
  VdlkinoEthernetUrl *func_url = this->urls;
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
    while (!block.valid && func_url) {
      func_url->function(&block, url);
      func_url = func_url->next;
    }
  }
  return block;
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
    this->replay(VDLKINO_ERROR);
  }
  this->client->stop();
}
