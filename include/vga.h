#ifndef _VGA_H
#define _VGA_H

#include "avr/io.h"
#include "avr/interrupt.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NOP
#define NOP __asm__("nop\n\t")
#endif

#define VGA_BUFFER_SIZE (1024)

#define VGA_HSYNC_TIMEOUT (512)

#define VGA_SCANLINE_START (-24)

#define VGA_SCANLINE_STOP (512)

#define VGA_SCANLINE_VSYNC_START (-24)

#define VGA_SCANLINE_VSYNC_STOP (-16)

#define VGA_TEXEL_SMALL (3)

#define VGA_TEXEL_MEDIUM (4)

#define VGA_TEXEL_LARGE (8)

#define VGA_TEXEL_HEIGHT VGA_TEXEL_MEDIUM

#define VGA_TEXEL_WIDTH NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;

#define VGA_RGB_OFF() (PORTB = 0)

#define VGA_RGB_SET(v) (PORTB = (v))

#define VGA_HSYNC_ON() (PORTD &= ~128)

#define VGA_HSYNC_OFF() (PORTD |= 128)

#define VGA_VSYNC_ON() (PORTD &= ~64)

#define VGA_VSYNC_OFF() (PORTD |= 64)

#define VGA_SET_HSYNC(v) (OCR1A = round ((v) / 4) * 4)

#define VGA_SET_VSYNC(v) (vga_scanline_stop = (v))

#define VGA_SET_TEXEL1D(i, v) (vga_buffer[(i)] = (v))

#define VGA_SET_TEXEL2D(x, y, v) (vga_buffer[(y) * 32 + (x)] = (v))

#define VGA_GET_TEXEL1D(i) (vga_buffer[(i)])

#define VGA_GET_TEXEL2D(x, y) (vga_buffer[(y) * 32 + (x)])

#define VGA_SET_TEXELHEIGHT(v) (vga_texel_height = (v) % 11)

#define VGA_SET_OFFSETX(x) (vga_offset_x = (x) & 31)

#define VGA_SET_OFFSETY(y) (vga_offset_y = ((y) & 31) * 32)

short int vga_scanline;
unsigned short int vga_scanline_stop;
char vga_buffer[VGA_BUFFER_SIZE];
char vga_offset_x;
unsigned short int vga_offset_y;
char vga_texel_height;

void vga_init (void);

#ifdef __cplusplus
}
#endif

#endif
