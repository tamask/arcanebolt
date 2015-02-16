#ifndef _PULSE_H
#define _PULSE_H

#ifdef __cplusplus
extern "C" {
#endif

#define PULSE_PIN (4)

#define PULSE_EVERY 0

#define PULSE_FOURTH 3

#define PULSE_EIGHTH 7

#define PULSE_SIXTEENTH 15

#define PULSE_STREAM_FUNCTION 0

#define PULSE_EVENT_FUNCTION 1

#define PULSE_FUNCTION_COUNT 8

#define PULSE_AMPLITUDE (pulse_amplitude)

#define PULSE_ISENABLED() (pulse_enabled)

#define PULSE_ENABLE() (pulse_enabled = 1)

#define PULSE_DISABLE() (pulse_enabled = 0)

#define PULSE_UPDATE() (pulse_enabled ? _pulse_update() : 0)

#define PULSE_RESET() (pulse_init())

#define PULSE_SET_FUNC(v) (pulse_current_i = (v) % PULSE_FUNCTION_COUNT)

#define PULSE_SET_DIV(v) (pulse_div = (v))

#define PULSE_SET_AMP(v) (pulse_amplitude = (v))

#define PULSE_SET_AMPDELTA(v) (pulse_amplitude += (v))

char pulse_enabled;
char pulse_div;
char pulse_tick;
char pulse_value;
char pulse_value_last;
char pulse_register_i;
int pulse_current_i;
short pulse_amplitude;

int pulse_modes[PULSE_FUNCTION_COUNT];
void (*pulse_funcs[PULSE_FUNCTION_COUNT])(char state);

void pulse_init (void);
int _pulse_update (void);
int pulse_register (char mode, void (*fn)(char state));

#ifdef __cplusplus
}
#endif

#endif
