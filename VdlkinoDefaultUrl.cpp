/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#include "Vdlkino.h"
#include "VdlkinoDefaultUrl.h"


void url_raw(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "raw")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->oper = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->pin = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->value = atoi(pc);
  vblock->valid = 1;
}


void url_digitalpins(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "digital")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc != NULL) {
    return;
  }
  vblock->oper = 0;
  vblock->pin = 0;
  vblock->value = 0;
  vblock->valid = 1;
}

void url_analogpins(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "analog")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc != NULL) {
    return;
  }
  vblock->oper = 1;
  vblock->pin = 0;
  vblock->value = 0;
  vblock->valid = 1;
}


void url_setpinmode(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "mode")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->pin = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->oper = 2;
  vblock->value = atoi(pc);
  vblock->valid = 1;
}

void url_getpinmode(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "mode")) {
    return;
  }

  pc = strtok(pc, "/");
  if (pc == NULL) {
    return;
  }
  vblock->pin = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc != NULL) {
    return;
  }
  vblock->oper = 3;
  vblock->value = 0;
  vblock->valid = 1;
}


void url_setdigital(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "digital")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->pin = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->oper = 4;
  vblock->value = atoi(pc);
  vblock->valid = 1;
}

void url_getdigital(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "digital")) {
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
  vblock->oper = 5;
  vblock->value = 0;
  vblock->valid = 1;
}


void url_setanalog(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "analog")) {
    return;
  }

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->pin = atoi(pc);

  pc = strtok(NULL, "/");
  if (pc == NULL) {
    return;
  }
  vblock->oper = 6;
  vblock->value = atoi(pc);
  vblock->valid = 1;
}

void url_getanalog(void *block, char *url) {
  VdlkinoBlock *vblock = (VdlkinoBlock*) block;
  char buffer[256];
  char *pc = buffer;

  strcpy(pc, url);
  if (pc[0] == '/') {
    pc++;
  }

  pc = strtok(pc, "/");
  if (strcmp(pc, "analog")) {
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
  vblock->oper = 7;
  vblock->value = 0;
  vblock->valid = 1;
}
