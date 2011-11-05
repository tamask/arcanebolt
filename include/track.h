#ifndef _TRACK_H
#define _TRACK_H

#include "data.h"
#include "vga.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  short int time;
  short int hsync;
  short int vsync;
} track_line_t;

#define TRACK_CHANNEL_HSYNC (1)

#define TRACK_CHANNEL_VSYNC (2)

#define TRACK_ISENABLED() (track_enabled)

#define TRACK_ENABLE() (track_enabled ? 0 : (track_enabled = 1))

#define TRACK_DISABLE() (track_enabled ? (track_enabled = 0) : 0)

#define TRACK_TOGGLE() (track_enabled ? TRACK_DISABLE () : TRACK_ENABLE ())

#define TRACK_SET_CHANNEL_MASK(m) (track_channel_mask = (m))

#define TRACK_ENABLE_CHANNEL(c) (track_channel_mask |= (c))
 
#define TRACK_DISABLE_CHANNEL(c) (track_channel_mask ^= (c))

#define TRACK_CHANNEL_ISENABLED(c) (track_channel_mask & (c))

#define TRACK_LOAD(i) (_track_load ((i)))

#define TRACK_UPDATE() (track_enabled ? _track_update () : 0)

char track_enabled;
char track_channel_mask;
char track_index;
unsigned long track_time;
unsigned short int track_cursor;
unsigned short int track_offset;
unsigned short int track_length;
track_line_t track_line;

void track_init (void);

int _track_load (int i);

int _track_update (void);

#ifdef __cplusplus
}
#endif

#endif
