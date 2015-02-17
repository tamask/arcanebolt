#ifndef _SCROLL_H
#define _SCROLL_H

#include "vga.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCROLL_SPEED_SLOWEST (31)

#define SCROLL_SPEED_SLOW (15)

#define SCROLL_SPEED_MEDIUM (7)

#define SCROLL_SPEED_FAST (3)

#define SCROLL_SPEED_FASTEST (0)

#define SCROLL_ISENABLED() (scroll_enabled)

#define SCROLL_ENABLE() (scroll_enabled = 1)

#define SCROLL_DISABLE() (scroll_enabled = 0)

#define SCROLL_TOGGLE() (scroll_enabled = !scroll_enabled)

#define SCROLL_UPDATE() (scroll_enabled ? (scroll_delta_x || scroll_delta_y ? _scroll_update (): 0) : 0)

#define SCROLL_SET_SPEED(v) (scroll_speed = (v))

#define SCROLL_SET_XDELTA(x) (scroll_delta_x -= (x))

#define SCROLL_SET_YDELTA(y) (scroll_delta_y -= (y))

#define SCROLL_RESET() (scroll_init())

#define SCROLL_CLEAR() (scroll_clear())

char scroll_enabled;
char scroll_tick;
char scroll_speed;
short int scroll_delta_x;
short int scroll_delta_y;
short int scroll_offset_x;
short int scroll_offset_y;

void scroll_init (void);

void scroll_clear (void);

int _scroll_update (void);

#ifdef __cplusplus
}
#endif

#endif
