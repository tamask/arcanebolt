#include "xt.h"
#include "vga.h"
#include "fill.h"
#include "blit.h"
#include "cursor.h"
#include "scroll.h"
#include "cycle.h"
#include "pulse.h"
#include "effects.h"

#define MODE_BLIT 0
#define MODE_CYCLE 1
#define MODE_PULSE 2
#define MODE_GET() (mode)
#define MODE_SET(v) (mode = (v))

xt_event_t e;
short int input_0;
short int input_1;
short int input_2;
unsigned int mode;

void
setup (void)
{
  xt_init ();
  vga_init ();
  fill_init ();
  blit_init ();
  cursor_init ();
  scroll_init ();
  cycle_init ();
  pulse_init ();
  effects_init ();

  MODE_SET (MODE_BLIT);
  VGA_SET_TEXELHEIGHT (VGA_TEXEL_SMALL);

  /* Serial.begin (9600); */
}

void
dump (void)
{
  /*
  int i;
  char cursor_state;

  cursor_state = CURSOR_ISENABLED ();
  CURSOR_DISABLE ();
  Serial.print (255, BYTE);
  for (i = 0; i < VGA_BUFFER_SIZE; i++)
    Serial.print (VGA_GET_TEXEL1D (i), BYTE);
  if (cursor_state)
    CURSOR_ENABLE ();
  */
}

void
loop (void)
{
  if (XT_EVENT (&e))
    {
      if (e.phase == XT_KEY_PRESS)
        {
          /* global commands */

          switch (e.symbol)
            {

            /* reset */

            case XT_ESCAPE:
              MODE_SET (MODE_BLIT);
              CURSOR_RESET ();
              SCROLL_RESET ();
              CYCLE_RESET ();
              FILL_SET (192);
              break;

            /* set mode */

            case XT_F1:
              MODE_SET (MODE_BLIT);
              break;
            case XT_F2:
              MODE_SET (MODE_CYCLE);
              break;
            case XT_F3:
              MODE_SET (MODE_PULSE);
              break;

            /* painting */

            case XT_TAB:
              CURSOR_TOGGLE ();
              CURSOR_SET_XABS (0);
              CURSOR_SET_YABS (0);
              CURSOR_SET_COLOR (26);
              break;
            case XT_A:
              CURSOR_SET_XDELTA (-1);
              break;
            case XT_S:
              CURSOR_SET_YDELTA (1);
              break;
            case XT_D:
              CURSOR_SET_XDELTA (1);
              break;
            case XT_W:
              CURSOR_SET_YDELTA (-1);
              break;
            case XT_Q:
              CURSOR_CYCLE_COLOR (-1);
              break;
            case XT_E:
              CURSOR_CYCLE_COLOR (1);
              break;

            /* scrolling */

            case XT_L:
              SCROLL_SET_XDELTA (-1);
              break;
            case XT_SEMICOLON:
              SCROLL_SET_YDELTA (1);
              break;
            case XT_APOSTROPHE:
              SCROLL_SET_XDELTA (1);
              break;
            case XT_P:
              SCROLL_SET_YDELTA (-1);
              break;
            case XT_O:
              SCROLL_SET_SPEED (SCROLL_SPEED_SLOWEST);
              break;
            case XT_COMMA:
              SCROLL_SET_SPEED (SCROLL_SPEED_SLOW);
              break;
            case XT_PERIOD:
              SCROLL_SET_SPEED (SCROLL_SPEED_MEDIUM);
              break;
            case XT_SLASH:
              SCROLL_SET_SPEED (SCROLL_SPEED_FAST);
              break;
            case XT_BRACKETLEFT:
              SCROLL_SET_SPEED (SCROLL_SPEED_FASTEST);
              break;
            case XT_M:
              SCROLL_RESET ();
              break;

            /* color cycling */

            case XT_Z:
              CYCLE_DISABLE ();
              break;
            case XT_X:
              CYCLE_ENABLE ();
              CYCLE_SET_SPEED (CYCLE_SPEED_SLOW);
              break;
            case XT_C:
              CYCLE_ENABLE ();
              CYCLE_SET_SPEED (CYCLE_SPEED_MEDIUM);
              break;
            case XT_V:
              CYCLE_ENABLE ();
              CYCLE_SET_SPEED (CYCLE_SPEED_FAST);
              break;

            /* pulsing */

            case XT_B:
              PULSE_DISABLE ();
              break;
            case XT_N:
              PULSE_ENABLE ();
              break;
            case XT_F:
              PULSE_ENABLE ();
              PULSE_SET_DIV (PULSE_EVERY);
              break;
            case XT_G:
              PULSE_ENABLE ();
              PULSE_SET_DIV (PULSE_FOURTH);
              break;
            case XT_H:
              PULSE_ENABLE ();
              PULSE_SET_DIV (PULSE_EIGHTH);
              break;
            case XT_J:
              PULSE_ENABLE ();
              PULSE_SET_DIV (PULSE_SIXTEENTH);
              break;

            /* misc/more painting */

            case XT_SPACE:
              CURSOR_TOGGLE_TRAIL ();
              break;
            case XT_ENTER:
              FILL_SET (CURSOR_GET_COLOR ());
              break;
            case XT_Y:
              dump ();
              break;
            }

          /* context dependent commands */

          if (e.symbol > 1 && e.symbol < 12)
            {
              switch (MODE_GET ())
                {
                case MODE_BLIT:
                  BLIT_SET
                    (CURSOR_GET_X (),
                     CURSOR_GET_Y (), e.symbol - 2);
                  break;

                case MODE_CYCLE:
                  CYCLE_ENABLE ();
                  CYCLE_LOAD (e.symbol - 2);
                  break;

                case MODE_PULSE:
                  PULSE_ENABLE ();
                  PULSE_SET_FUNC (e.symbol - 2);
                  break;
                }
            }
        }
    }

  input_0 = analogRead (0) >> 1;
  input_1 = analogRead (1) >> 2;
  input_2 = analogRead (2) >> 3;

  VGA_SET_HSYNC (input_0 + input_2);
  VGA_SET_VSYNC (input_1 + pulse_value);

  FILL_UPDATE ();
  BLIT_UPDATE ();
  CURSOR_UPDATE ();
  SCROLL_UPDATE ();
  CYCLE_UPDATE ();
  PULSE_UPDATE ();
}
