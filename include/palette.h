#ifndef _PALETTE_H
#define _PALETTE_H

#ifdef __cplusplus
extern "C" {
#endif

#define PALETTE_COLOR(v) (palette_colors[(v)])

#define PALETTE_BLACK 0
#define PALETTE_WHITE 26
#define PALETTE_CLEAR 27

extern const char *palette_colors;

#ifdef __cplusplus
}
#endif

#endif
