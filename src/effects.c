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
effects_cycle (char mode)
{
  if (mode)
    CYCLE_ENABLE ();
  else
    CYCLE_DISABLE ();
}

void
effects_randomblit (char mode)
{
  int i;
  char x, y;

  if (mode)
    {
      i = PULSE_AMPLITUDE;
      if (i < 0)
        i = DATA_IMAGE_COUNT - abs(i) % DATA_IMAGE_COUNT;
      i %= DATA_IMAGE_COUNT;

      x = (char)(random () % 32);
      y = (char)(random () % 32);

      BLIT_SET (x, y, i);
    }
}

void
effects_init ()
{
  pulse_register (PULSE_STREAM_FUNCTION, effects_hsync);
  pulse_register (PULSE_EVENT_FUNCTION, effects_scroll);
  pulse_register (PULSE_EVENT_FUNCTION, effects_cycle);
  pulse_register (PULSE_EVENT_FUNCTION, effects_randomblit);
}
