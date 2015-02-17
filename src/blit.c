#include "blit.h"

void
blit_init (void)
{
  blit_enabled = 0;
}

int
_blit_set (char x, char y, char i)
{
  if (i < image_count)
    {
      if (x > 31) x = 31;
      if (y > 31) y = 31;

      blit_x = x;
      blit_y = y;

      if (i < 0)
        i = 0;
      i %= DATA_IMAGE_COUNT;

      blit_image_index = i;
      blit_image_line = 0;
      blit_image_width = pgm_read_word (&(image_size[i][0]));
      blit_image_height = pgm_read_word (&(image_size[i][1]));
      blit_cursor_state = CURSOR_ISENABLED ();
      blit_cycle_state = CYCLE_ISENABLED ();

      CYCLE_DISABLE ();

      blit_enabled = 1;
    }
}

int
_blit_update (void)
{
  char p, i, x, y;

  if (blit_image_line < blit_image_height)
    {
      y = (blit_y + blit_image_line) & 31;

      for (i = 0; i < blit_image_width; i++)
        {
          x = (blit_x + i) & 31;

          memcpy_P (&p, (void *) (
            pgm_read_word (&(image_data[blit_image_index])) +
            (blit_image_width * blit_image_line + i)), 1);

          if (!(p & BLIT_MASK))
            VGA_SET_TEXEL2D (x, y, p);
        }

      blit_image_line++;
    }
  else
    {
      if (blit_cursor_state)
        CURSOR_ENABLE ();
      if (blit_cycle_state)
        CYCLE_ENABLE ();
      blit_enabled = 0;
    }

  return 0;
}
