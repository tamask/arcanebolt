#include "cycle.h"

void
cycle_init (void)
{
  cycle_enabled = 0;
  cycle_tick = 0;
  cycle_speed = CYCLE_SPEED_MEDIUM;
  CYCLE_LOAD (0);
}

int
_cycle_update (void)
{
  int i;
  char p;

  if ((cycle_tick++ & cycle_speed) == 0)
    {
      for (i = 0; i < VGA_BUFFER_SIZE; i++)
        {
          p = VGA_GET_TEXEL1D (i);
          if (!(p & CYCLE_MASK))
            VGA_SET_TEXEL1D(i, cycle_buffer[p]);
        }
      CURSOR_SET_BUFFER (cycle_buffer[CURSOR_GET_BUFFER ()]);
    }

  return 0;
}
