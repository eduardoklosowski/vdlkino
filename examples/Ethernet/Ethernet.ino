#include <SPI.h>
#include <Ethernet.h>
#include "VdlkinoEthernet.h"

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,177);
EthernetServer server(80);
VdlkinoEthernet vdlkino(14, 6, &server);

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {
  vdlkino.run();
}
