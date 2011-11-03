#include "fill.h"

void
fill_init (void)
{
  fill_enabled = 0;
  fill_line = 0;
}

int
_fill_set (char c)
{
  fill_color = c;
  fill_enabled = 1;
}

int
_fill_update (void)
{
  int i;

  if (fill_line < 32)
    {
      for (i = 0; i < 32; i++)
        VGA_SET_TEXEL2D (i, fill_line, fill_color);
      if (CURSOR_GET_Y () == fill_line)
        CURSOR_SET_BUFFER (fill_color);
      fill_line++;
    }
  else
    {
      fill_line = 0;
      fill_enabled = 0;
    }
  return 0;
}
