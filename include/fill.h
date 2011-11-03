#ifndef _FILL_H
#define _FILL_H

#include "vga.h"
#include "cursor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FILL_SET(c) (fill_enabled ? 0 : _fill_set (c))

#define FILL_UPDATE() (fill_enabled ? _fill_update () : 0)

#define FILL_FINISHED() (~fill_enabled)

char fill_enabled;
char fill_line;
char fill_color;

void fill_init (void);

int _fill_set (char c);

int _fill_update (void);

#ifdef __cplusplus
}
#endif

#endif
