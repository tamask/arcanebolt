#include "effects.h"

void
effects_hsync (char value)
{
  VGA_SET_HSYNC (VGA_GET_HSYNC () + value * PULSE_AMPLITUDE);
}

void
effects_scroll (char mode)
{
  if (mode)
    SCROLL_ENABLE ();
  else
    SCROLL_DISABLE ();
}

void
effects_decay (char mode)
{
  int i;
  char x, y;

  if (mode)
    {
      x = (char)(random () % 32);
      y = (char)(random () % 32);
      /* BLIT_SET (x, y, 0); */
      VGA_SET_TEXEL2D (x, y, 63);
    }
}

void
effects_init ()
{
  pulse_register (PULSE_STREAM_FUNCTION, effects_hsync);
  pulse_register (PULSE_EVENT_FUNCTION, effects_scroll);
  pulse_register (PULSE_EVENT_FUNCTION, effects_decay);
}
