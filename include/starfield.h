#ifndef _STARFIELD_H
#define _STARFIELD_H

#include "vga.h"
#include "palette.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STARFIELD_STAR_COUNT 16

#define STARFIELD_MODE_PERSPECTIVE 0

#define STARFIELD_MODE_SIDESCROLL 1

#define STARFIELD_SPEED_SLOW (31)

#define STARFIELD_SPEED_MEDIUM (7)

#define STARFIELD_SPEED_FAST (0)

#define STARFIELD_ISENABLED() (starfield_enabled)

#define STARFIELD_ENABLE() (starfield_enabled = 1)

#define STARFIELD_DISABLE() (starfield_enabled = 0)

#define STARFIELD_TOGGLE() (starfield_enabled = !starfield_enabled)

#define STARFIELD_SETMODE(v) (starfield_mode = (v))

#define STARFIELD_UPDATE() (starfield_enabled ? starfield_update () : 0)

typedef struct {
  signed char x;
  signed char y;
  signed char delta_x;
  signed char delta_y;
} starfield_star;

char starfield_enabled;
char starfield_mode;
char starfield_tick;
char starfield_speed;
starfield_star starfield_stars[STARFIELD_STAR_COUNT];

void starfield_init (void);

int starfield_update (void);

#ifdef __cplusplus
}
#endif

#endif
