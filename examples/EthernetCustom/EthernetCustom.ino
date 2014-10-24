#include <SPI.h>
#include <Ethernet.h>
#include "VdlkinoEthernet.h"

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,177);
EthernetServer server(80);
VdlkinoEthernet vdlkino(14, 6, &server);

void url_get_analog_byte(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "analogbyte")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->pin = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc != NULL) {
    return;
  }
  vblock->oper = 8;
  vblock->value = 0;
  vblock->valid = 1;
}

uint16_t get_analog_byte(void *block) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  return map(analogRead(vblock->pin), 0, 1023, 0, 255);
}

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  vdlkino.operations[8] = &get_analog_byte;
  vdlkino.addUrl(&url_get_analog_byte);
}

void loop() {
  vdlkino.run();
}
