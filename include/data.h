#ifndef _DATA_H
#define _DATA_H

#include "avr/pgmspace.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char image_count;
extern char cycle_count;
extern char track_count;
extern unsigned short int track_size[][2];
extern prog_uint16_t image_size[][2] PROGMEM;
extern const char *image_data[] PROGMEM;
extern prog_char cycle_data[] PROGMEM;
extern prog_int16_t track_data[] PROGMEM;

#ifdef __cplusplus
}
#endif

#endif
