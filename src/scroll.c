#include "scroll.h"

void
scroll_init (void)
{
  scroll_enabled = 0;
  scroll_tick = 0;
  scroll_speed = SCROLL_SPEED_SLOW;
  scroll_delta_x = 0;
  scroll_delta_y = 0;
  scroll_offset_x = 0;
  scroll_offset_y = 0;

  VGA_SET_OFFSETX (0);
  VGA_SET_OFFSETY (0);
}

int
_scroll_update (void)
{
  if ((scroll_tick++ & scroll_speed) == 0)
    {
      scroll_offset_x += scroll_delta_x;
      scroll_offset_y += scroll_delta_y;

      VGA_SET_OFFSETX (scroll_offset_x);
      VGA_SET_OFFSETY (scroll_offset_y);
    }

  return 0;
}
