#include "cursor.h"

void
cursor_init (void)
{
  cursor_buffer = VGA_GET_TEXEL2D (cursor_x, cursor_y);
  cursor_counter = 0;
  cursor_enabled = 0;
  cursor_trail = 0;
  cursor_x = 0;
  cursor_y = 0;
  cursor_color = PALETTE_WHITE;
  cursor_target_x = 0;
  cursor_target_y = 0;
}

int
_cursor_update (void)
{
  if (cursor_target_x != cursor_x ||
      cursor_target_y != cursor_y)
    {
      if (cursor_target_x < 0)
        cursor_target_x = 31;
      if (cursor_target_x > 31)
        cursor_target_x = 0;
      if (cursor_target_y < 0)
        cursor_target_y = 31;
      if (cursor_target_y > 31)
        cursor_target_y = 0;

      if (!cursor_trail)
        VGA_SET_TEXEL2D (cursor_x, cursor_y, cursor_buffer);
      else
        VGA_SET_TEXEL2D (cursor_x, cursor_y, PALETTE_COLOR (cursor_color));
      cursor_x = cursor_target_x;
      cursor_y = cursor_target_y;
      cursor_buffer = VGA_GET_TEXEL2D (cursor_x, cursor_y);
    }

  if (cursor_counter == 0)
    VGA_SET_TEXEL2D (cursor_x, cursor_y, 0);
  else if (cursor_counter == 20)
    VGA_SET_TEXEL2D (cursor_x, cursor_y, PALETTE_COLOR (cursor_color));

  if (cursor_counter++ > 40)
    cursor_counter = 0;

  return 0;
}
