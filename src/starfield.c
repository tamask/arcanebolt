#include "starfield.h"

inline void
starfield_spawn (starfield_star *star)
{
  star->x = star->delta_x * (rand() % 31);
  star->y = star->delta_y * (rand() % 31);
}

inline void
starfield_setdelta (starfield_star *star)
{
  int x, y;

  x = rand() % 8;
  y = rand() % 8;
  x -= 4;
  y -= 4;

  if (x == 0)
    x = (rand() % 2) == 0 ? -1 : 1;
  if (y == 0)
    y = (rand() % 2) == 0 ? -1 : 1;

  star->delta_x = x;
  star->delta_y = y;
}

void
starfield_init (void)
{
  int i;
  starfield_star *star;

  starfield_tick = 0;
  starfield_enabled = 0;
  starfield_speed = STARFIELD_SPEED_FAST;

  for (i = 0; i < STARFIELD_STAR_COUNT; i++)
    {
      star = &starfield_stars[i];
      starfield_setdelta (star);
      starfield_spawn (star);
    }
}

int
starfield_update (void)
{
  int i;
  int x;
  int y;
  unsigned int abs_x;
  unsigned int abs_y;
  char sign;
  char color;
  starfield_star *star;

  if ((starfield_tick++ & starfield_speed) == 0)
    {
      VGA_CLEAR ();

      if (starfield_mode == 1)
        {
          for (i = 0; i < STARFIELD_STAR_COUNT; i++)
            {
              star = &starfield_stars[i];

              x = star->x - abs (star->delta_x);
              y = star->y;

              if (x < -126)
                {
                  x = star->x = 126;
                  y = star->y = rand() % 255 - 127;
                }

              star->x = x;
              star->y = y;

              x = (x / 4 + 32) / 2;
              y = (y / 4 + 32) / 2;

              if (abs (star->delta_x) < 3)
                color = PALETTE_GREY;
              else
                color = PALETTE_WHITE;

              VGA_SET_TEXEL2D (x, y, color);
            }
        }
      else
        {
          for (i = 0; i < STARFIELD_STAR_COUNT; i++)
            {
              star = &starfield_stars[i];

              x = star->x + star->delta_x;
              y = star->y + star->delta_y;
              abs_x = abs (x);
              abs_y = abs (y);

              if (abs_x > 126 ||
                  abs_y > 126)
                {
                  x = y = abs_x = abs_y = 0;
                  starfield_setdelta (star);
                }

              star->x = x;
              star->y = y;

              if (abs_x < 64 && abs_y < 64)
                color = PALETTE_BLACK;
              else if (abs_x < 92 && abs_y < 92)
                color = PALETTE_GREY;
              else
                color = PALETTE_WHITE;

              sign = x < 0 ? -1 : 1;
              x = (x * x >> 7) * sign;
              sign = y < 0 ? -1 : 1;
              y = (y * y >> 7) * sign;

              x = (x / 4 + 32) / 2;
              y = (y / 4 + 32) / 2;

              VGA_SET_TEXEL2D (x, y, color);
            }
        }
    }

  return 1;
}
