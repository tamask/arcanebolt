#include "vga.h"

void
vga_init (void)
{
  int i;

  /* color pins */
  DDRB = 63; /* 00111111 */

  /* hsync/vsync pins */
  DDRD = DDRD = PORTD = 192; /* 11000000 */

  /* initialize hsync timer */
  TIMSK0 &= !(1 << TOIE0);
  cli();
  TCCR1A = 0;
  TCCR1B = 1 << WGM22 | 1 << CS10;
  OCR1A = VGA_HSYNC_TIMEOUT;
  TIMSK1 = 1 << OCIE1A;
  sei();

  vga_offset_x = 0;
  vga_offset_y = 0;
  vga_scanline = VGA_SCANLINE_START;
  vga_scanline_stop = VGA_SCANLINE_STOP;
  vga_texel_height = VGA_TEXEL_HEIGHT;

  for (i = 0; i < VGA_BUFFER_SIZE; i++)
    VGA_SET_TEXEL1D (i, 192); /* set transparent */
}

ISR (TIMER1_COMPA_vect)
{
  unsigned short int o;

  /* vsync pulse (spans lines) */
  switch (vga_scanline)
    {
    case VGA_SCANLINE_VSYNC_START:
      VGA_VSYNC_ON ();
      break;
    case VGA_SCANLINE_VSYNC_STOP:
      VGA_VSYNC_OFF ();
      break;
    }

  /* hsync pulse */
  VGA_HSYNC_ON ();
  NOP; NOP; NOP; NOP; NOP;
  NOP; NOP; NOP; NOP; NOP;
  VGA_HSYNC_OFF ();

  /* left margin */
  NOP; NOP; NOP; NOP; NOP;
  NOP; NOP; NOP; NOP; NOP;

  if (vga_scanline > -1)
    {
      /* bitwise multiplication/division/modulo */
      o = (vga_offset_y + (vga_scanline >> vga_texel_height << 5)) & 1023;

      /* draw 32 elements in the buffer */
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 0) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 1) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 2) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 3) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 4) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 5) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 6) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 7) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 8) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 9) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 10) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 11) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 12) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 13) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 14) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 15) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 16) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 17) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 18) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 19) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 20) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 21) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 22) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 23) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 24) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 25) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 26) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 27) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 28) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 29) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 30) & 31)]);
      VGA_RGB_SET (vga_buffer[o + ((vga_offset_x + 31) & 31)]);
      VGA_TEXEL_WIDTH;

      VGA_RGB_OFF ();
    }

  if (++vga_scanline == vga_scanline_stop)
    vga_scanline = VGA_SCANLINE_START;
}
