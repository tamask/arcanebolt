#include "vga.h"
#include "blit.h"
#include "scroll.h"
#include "cycle.h"

short int input_0;
short int input_1;
short int input_2;
short int input_3;
short int input_4;

void
setup (void)
{
  vga_init ();
  blit_init ();
  scroll_init ();
  cycle_init ();

  VGA_SET_TEXELHEIGHT (VGA_TEXEL_SMALL);

  BLIT_SET(0, 0, 0);
}

void
loop (void)
{
  input_0 = analogRead (0);
  input_1 = analogRead (1);

  BLIT_UPDATE ();
  SCROLL_UPDATE ();
  CYCLE_UPDATE ();

  VGA_SET_HSYNC (input_0);
  VGA_SET_VSYNC (input_1);
}
