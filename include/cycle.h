#ifndef _CYCLE_H
#define _CYCLE_H

#include "data.h"
#include "vga.h"
#include "cursor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CYCLE_MASK (192) /* 11000000 */

#define CYCLE_SPEED_SLOW (31)

#define CYCLE_SPEED_MEDIUM (7)

#define CYCLE_SPEED_FAST (0)

#define CYCLE_ISENABLED() (cycle_enabled)

#define CYCLE_ENABLE() (cycle_enabled = 1)

#define CYCLE_DISABLE() (cycle_enabled = 0)

#define CYCLE_LOAD(i) ((i) < cycle_count ? memcpy_P (cycle_buffer, cycle_data + (64 * (i)), 64) : 0)

#define CYCLE_UPDATE() (cycle_enabled ? _cycle_update() : 0)

#define CYCLE_SET_SPEED(v) (cycle_speed = (v))

#define CYCLE_RESET() (cycle_init())

char cycle_enabled;
char cycle_tick;
char cycle_speed;
char cycle_buffer[64];

void cycle_init (void);
int _cycle_update (void);

#ifdef __cplusplus
}
#endif

#endif
