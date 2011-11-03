#include "xt.h"

void
xt_init (void)
{
  xt_ready = 0;
  xt_shift = 256; /* 1 << 8 */
  xt_scancode = 0;
  xt_modifiers = 0;
  xt_escape = 0;

  EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (XT_FALLING << ISC00);
  EIMSK |= (1 << INT0);
}

ISR (INT0_vect)
{
  /* PORTD |= XT_PIN_DATA; */
  if (xt_ready == 0)
    {
      if (xt_shift == 256) /* 1 << 8 */
        /* start bit */
        xt_shift = 1;
      else
        {
          /* data bits */
          if (PIND & XT_PIN_DATA)
            xt_scancode |= xt_shift;
          xt_shift <<= 1;
          if (xt_shift == 256) /* 1 << 8 */
            xt_ready = 1;
        }
    }
  /* PORTD &= 0; */
}

int
_xt_event (xt_event_t *e)
{
  unsigned int modifiers;

  ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    {
      /* Two escape scancodes are used, 0xe0 and 0xe1, as 'namespaces' */
      /* for subsequence scancodes.  We don't process the escapes, just */
      /* set the escape state in the context. */
      /* TODO: handle 0xe1 escape sequences (there are only 4) */
      if (xt_scancode != 0xe0 || xt_scancode != 0xe1)
        {
          modifiers = 0;

          /* Unset the high bit from the scancode, and mask it with */
          /* the escape code if its set. */
          e->symbol = xt_escape << 8 | xt_scancode & ~128; /* 1 << 7 */

          /* The high bit determines if it is a key press or release. */
          if (xt_scancode & 128)
            e->phase = XT_KEY_RELEASE;
          else
            e->phase = XT_KEY_PRESS;

          e->modifiers = xt_modifiers;

          /* If the key is a modifier, toggle the modifier in the context. */
          switch (e->symbol)
            {
            case 0x2a:
              modifiers |= XT_MOD_SHIFT;
              break;
            case 0x45:
              modifiers |= XT_MOD_NUMLOCK;
              break;
            case 0x1d:
              modifiers |= XT_MOD_CTRL;
              break;
            case 0x28:
              modifiers |= XT_MOD_ALT;
              break;
            case 0x3a:
              modifiers |= XT_MOD_CAPSLOCK;
              break;
            case 0x56:
              modifiers |= XT_MOD_SUPER;
              break;
            case 0x46:
              modifiers |= XT_MOD_SCROLLLOCK;
              break;
            }
          if (e->phase == XT_KEY_PRESS)
            xt_modifiers |= modifiers;
          else
            xt_modifiers &= ~modifiers;

          xt_escape = 0;
        }
      else
        xt_escape = 0xe0;

      xt_scancode = xt_ready = 0;
      return 1;
    }
}
