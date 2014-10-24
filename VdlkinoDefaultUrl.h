/*
 * Copyright (c) 2014 Eduardo Klosowski
 * License: MIT (see LICENSE for details)
 */

#ifndef vdlkinodefaulturl_h
#define vdlkinodefaulturl_h

void url_raw(void *block, char *url);

void url_digitalpins(void *block, char *url);
void url_analogpins(void *block, char *url);

void url_setpinmode(void *block, char *url);
void url_getpinmode(void *block, char *url);

void url_setdigital(void *block, char *url);
void url_getdigital(void *block, char *url);

void url_setanalog(void *block, char *url);
void url_getanalog(void *block, char *url);

#endif
