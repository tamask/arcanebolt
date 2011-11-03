#ifndef _CURSOR_H
#define _CURSOR_H

#include "vga.h"
#include "palette.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CURSOR_ISENABLED() (cursor_enabled)

#define CURSOR_ENABLE() (cursor_enabled ? 0 : (cursor_enabled = 1) && (cursor_buffer = VGA_GET_TEXEL2D (cursor_x, cursor_y)))

#define CURSOR_DISABLE() (cursor_enabled ? (cursor_enabled = 0) || VGA_SET_TEXEL2D (cursor_x, cursor_y, cursor_buffer) : 0)

#define CURSOR_TOGGLE() (cursor_enabled ? CURSOR_DISABLE () : CURSOR_ENABLE ())

#define CURSOR_TOGGLE_TRAIL() (cursor_trail ^= 1)

#define CURSOR_UPDATE() (cursor_enabled ? _cursor_update () : 0)

#define CURSOR_SET_BUFFER(v) (cursor_buffer = (v))

#define CURSOR_SET_XABS(x) (cursor_target_x = (x))

#define CURSOR_SET_XDELTA(x) (cursor_target_x = (cursor_x + x))

#define CURSOR_SET_YABS(y) (cursor_target_y = (y))

#define CURSOR_SET_YDELTA(y) (cursor_target_y = (cursor_y + y))

#define CURSOR_SET_COLOR(v) (cursor_color = (v))

#define CURSOR_CYCLE_COLOR(v) ((cursor_color + v) < 0 ? (cursor_color = 27) : (cursor_color = (cursor_color + (v)) % 28))

#define CURSOR_GET_X() (cursor_x)

#define CURSOR_GET_Y() (cursor_y)

#define CURSOR_GET_BUFFER() (cursor_buffer)

#define CURSOR_GET_COLOR() (PALETTE_COLOR (cursor_color))

#define CURSOR_RESET() (cursor_init())

char cursor_counter;
char cursor_enabled;
char cursor_trail;
char cursor_buffer;
char cursor_x;
char cursor_y;
char cursor_color;
short int cursor_target_x;
short int cursor_target_y;

void cursor_init (void);

int _cursor_update (void);

#ifdef __cplusplus
}
#endif

#endif
