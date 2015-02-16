#ifndef _BLIT_H
#define _BLIT_H

#include "avr/pgmspace.h"
#include "data.h"
#include "vga.h"
#include "cursor.h"
#include "cycle.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLIT_MASK (192) /* B11000000 */

#define BLIT_SET(x, y, i) (blit_enabled ? 0 : _blit_set (x, y, i))

#define BLIT_GET() (blit_image_index);

#define BLIT_UPDATE() (blit_enabled ? _blit_update () : 0)

#define BLIT_FINISHED() (~blit_enabled)

char blit_enabled;
char blit_x;
char blit_y;
char blit_image_index;
char blit_image_line;
char blit_image_width;
char blit_image_height;
char blit_cursor_state;
char blit_cycle_state;

void blit_init (void);

int _blit_set (char x, char y, char i);

int _blit_update (void);

#ifdef __cplusplus
}
#endif

#endif
