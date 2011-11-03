#ifndef _DATA_H
#define _DATA_H

#include "avr/pgmspace.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char image_count;
extern char cycle_count;
extern prog_uint16_t image_size[][2] PROGMEM;
extern const char *image_data[] PROGMEM;
extern prog_char cycle_data[] PROGMEM;

#ifdef __cplusplus
}
#endif

#endif
