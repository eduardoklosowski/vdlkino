/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#ifndef vdlkinoethernet_h
#define vdlkinoethernet_h

#include <Ethernet.h>
#include "Vdlkino.h"


class VdlkinoEthernet;
class VdlkinoEthernetUrl;


class VdlkinoEthernet: public Vdlkino {
public:
  EthernetServer *server;
  EthernetClient *client;
  char access[256];
  VdlkinoEthernetUrl *urls;

  VdlkinoEthernet(uint8_t digital, uint8_t analog, EthernetServer *server);
  void addUrl(void (*function) (void*, char*));
  virtual VdlkinoBlock getBlock();
  virtual void replay(uint16_t value);
  virtual void run();
};


class VdlkinoEthernetUrl {
public:
  void (*function) (void*, char *url);
  VdlkinoEthernetUrl *next;

  VdlkinoEthernetUrl(void (*function) (void*, char*)) {
    this->function = function;
    this->next = 0;
  };
};

#endif
