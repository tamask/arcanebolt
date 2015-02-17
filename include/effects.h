#ifndef _EFFECTS_H
#define _EFFECTS_H

#include "vga.h"
#include "blit.h"
#include "pulse.h"
#include "cycle.h"
#include "scroll.h"
#include "input.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFFECTS_RESET() (effects_init())

void effects_init ();

#ifdef __cplusplus
}
#endif

#endif
