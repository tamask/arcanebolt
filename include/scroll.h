#ifndef _SCROLL_H
#define _SCROLL_H

#include "vga.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCROLL_SPEED_SLOW (31)

#define SCROLL_SPEED_MEDIUM (3)

#define SCROLL_SPEED_FAST (0)

#define SCROLL_UPDATE() (scroll_delta_x || scroll_delta_y ? _scroll_update (): 0)

#define SCROLL_SET_SPEED(v) (scroll_speed = (v))

#define SCROLL_SET_XDELTA(x) (scroll_delta_x -= (x))

#define SCROLL_SET_YDELTA(y) (scroll_delta_y -= (y))

#define SCROLL_RESET() (scroll_init())

char scroll_tick;
char scroll_speed;
short int scroll_delta_x;
short int scroll_delta_y;
short int scroll_offset_x;
short int scroll_offset_y;

void scroll_init (void);

int _scroll_update (void);

#ifdef __cplusplus
}
#endif

#endif
