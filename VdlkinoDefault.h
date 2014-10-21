/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#ifndef vdlkinodefault_h
#define vdlkinodefault_h

uint16_t oper_digitalpins(void *block);
uint16_t oper_analogpins(void *block);

uint16_t oper_setpinmode(void *block);
uint16_t oper_getpinmode(void *block);

uint16_t oper_setdigital(void *block);
uint16_t oper_getdigital(void *block);

uint16_t oper_setanalog(void *block);
uint16_t oper_getanalog(void *block);

#endif
