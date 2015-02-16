#include "pulse.h"

void
pulse_init (void)
{
  int i;

  pulse_enabled = 0;
  pulse_value = 0;
  pulse_register_i = 0;
  pulse_current_i = 0;

  for (i = 0; i < PULSE_FUNCTION_COUNT; i++)
    {
      pulse_modes[i] = 0;
      pulse_funcs[i] = 0;
    }
}

int
_pulse_update (void)
{
  int i;
  char trigger;

  trigger = 0;
  pulse_value = digitalRead (PULSE_PIN);

  switch (pulse_modes[pulse_current_i])
    {
    case PULSE_EVENT_FUNCTION:
      if (pulse_value && !pulse_value_last)
        trigger = 1;
      if (!pulse_value && pulse_value_last)
        trigger = 1;

      if (trigger)
        pulse_funcs[pulse_current_i](pulse_value);
      break;

    case PULSE_STREAM_FUNCTION:
      pulse_funcs[pulse_current_i](pulse_value);
    }

  pulse_value_last = pulse_value;

  return 0;
}

int
pulse_register (char mode, void (*fn)(char state))
{
  if (pulse_register_i == PULSE_FUNCTION_COUNT)
    return 1;

  else
    {
      pulse_modes[pulse_register_i] = mode;
      pulse_funcs[pulse_register_i] = fn;
      pulse_register_i++;

      return 0;
    }
}
