#include "vga.h"
#include "blit.h"
#include "scroll.h"
#include "cycle.h"

#define MODE_BLIT 0
#define MODE_CYCLE 1
#define MODE_SCROLL_X 2
#define MODE_SCROLL_Y 3
#define MODE_GET() (mode)
#define MODE_SET(v) (mode = (v))

short int input_0;
short int input_1;
short int input_2;
short int input_3;
short int input_4;
unsigned int mode;
short int input_1_normalized;

void
setup (void)
{
  vga_init ();
  blit_init ();
  scroll_init ();
  cycle_init ();

  MODE_SET (MODE_BLIT);
  VGA_SET_TEXELHEIGHT (VGA_TEXEL_SMALL);
}

void
loop (void)
{
  input_0 = analogRead (0);
  input_1 = analogRead (1);

  /* 4 modes, input_0 has a range of 0-1023 */
  MODE_SET (input_0 / 256);

  switch (MODE_GET ())
    {

    case MODE_BLIT:
      /* 9 images to blit */
      if ((input_1 / 103) != input_1_normalized) {
        input_1_normalized = input_1 / 103;
        BLIT_SET (0, 0, input_1_normalized);
      }
      break;

    case MODE_CYCLE:
      /* 9 images to blit */
      if ((input_1 / 256) != input_1_normalized) {
        input_1_normalized = input_1 / 256;
        if (input_1_normalized == 0)
          CYCLE_DISABLE ();
        else {
          CYCLE_ENABLE ();
          switch (input_1_normalized)
            {
            case 1:
              CYCLE_SET_SPEED (CYCLE_SPEED_SLOW);
              break;
            case 2:
              CYCLE_SET_SPEED (CYCLE_SPEED_MEDIUM);
              break;
            case 3:
              CYCLE_SET_SPEED (CYCLE_SPEED_FAST);
              break;
            }
        }
      }
      break;

    case MODE_SCROLL_X:
      input_1_normalized = input_1 / 102 - 5;
      SCROLL_SET_ABSXDELTA (input_1_normalized);
      break;

    case MODE_SCROLL_Y:
      input_1_normalized = input_1 / 102 - 5;
      SCROLL_SET_ABSYDELTA (input_1_normalized);
      break;

    }

  BLIT_UPDATE ();
  SCROLL_UPDATE ();
  CYCLE_UPDATE ();

  input_2 = analogRead (2) >> 1;
  input_3 = analogRead (3) >> 2;
  input_4 = analogRead (4) >> 3;

  VGA_SET_HSYNC (input_2 + input_4);
  VGA_SET_VSYNC (input_3);
}
