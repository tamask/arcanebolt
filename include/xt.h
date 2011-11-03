#ifndef _XT_H
#define _XT_H

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XT_FALLING (2)

#define XT_PIN_DATA (8) /* 1 << 3 */

#define XT_EVENT(e) (xt_ready != 0 ? _xt_event (e) : 0)

char xt_ready;
unsigned int xt_shift;
unsigned int xt_scancode;
unsigned int xt_modifiers;
unsigned int xt_escape;

typedef struct {
  char phase;
  unsigned int symbol;
  unsigned int modifiers;
} xt_event_t;

void xt_init ();

int _xt_event (xt_event_t *e);

#define XT_KEY_PRESS 1
#define XT_KEY_RELEASE 0
#define XT_MOD_SHIFT 1
#define XT_MOD_CTRL 2
#define XT_MOD_ALT 4
#define XT_MOD_CAPSLOCK 16
#define XT_MOD_NUMLOCK 32
#define XT_MOD_SUPER 64
#define XT_MOD_SCROLLLOCK 128
#define XT_0 0x0b
#define XT_1 0x02
#define XT_2 0x03
#define XT_3 0x04
#define XT_4 0x05
#define XT_5 0x06
#define XT_6 0x07
#define XT_7 0x08
#define XT_8 0x09
#define XT_9 0x0a
#define XT_A 0x1e
#define XT_B 0x30
#define XT_C 0x2e
#define XT_D 0x20
#define XT_E 0x12
#define XT_F 0x21
#define XT_G 0x22
#define XT_H 0x23
#define XT_I 0x17
#define XT_J 0x24
#define XT_K 0x25
#define XT_L 0x26
#define XT_M 0x32
#define XT_N 0x31
#define XT_O 0x18
#define XT_P 0x19
#define XT_Q 0x10
#define XT_R 0x13
#define XT_S 0x1f
#define XT_T 0x14
#define XT_U 0x16
#define XT_V 0x2f
#define XT_W 0x11
#define XT_X 0x2d
#define XT_Y 0x15
#define XT_Z 0x2c
#define XT_F1 0x3b
#define XT_F2 0x3c
#define XT_F3 0x3d
#define XT_F4 0x3e
#define XT_F5 0x3f
#define XT_F6 0x40
#define XT_F7 0x41
#define XT_F8 0x42
#define XT_F9 0x43
#define XT_F10 0x44
#define XT_F11 0x57
#define XT_F12 0x58
#define XT_ESCAPE 0x01
#define XT_GRAVE 0x29
#define XT_QUOTELEFT 0x29
#define XT_BRACKETLEFT 0x1a
#define XT_BRACKETRIGHT 0x1b
#define XT_BACKSLASH 0x2b
#define XT_SEMICOLON 0x27
#define XT_APOSTROPHE 0x28
#define XT_COMMA 0x33
#define XT_PERIOD 0x34
#define XT_SLASH 0x35
#define XT_MINUS 0x0c
#define XT_EQUAL 0x0d
#define XT_TAB 0x0f
#define XT_ENTER 0x1c
#define XT_RETURN 0x1c
#define XT_BACKSPACE 0x0e
#define XT_CAPSLOCK 0x3a
#define XT_LSHIFT 0x2a
#define XT_RSHIT 0x36
#define XT_LCTRL 0x1d
#define XT_RCTRL 0xe01d
#define XT_LALT 0x38
#define XT_RALT 0xe038
#define XT_SPACE 0x39
#define XT_PRINT 0xe02ae037
#define XT_SYSREQ 0xe02ae037
#define XT_SCROLLLOCK 0x46
#define XT_BREAK 0xe11d45e19dc5
#define XT_PAUSE 0xe11d45e19dc5
#define XT_INSERT 0xe052
#define XT_DELETE 0xe053
#define XT_HOME 0xe047
#define XT_END 0xe04f
#define XT_PAGEUP 0xe049
#define XT_PAGEDOWN 0xe051
#define XT_UP 0xe048
#define XT_LEFT 0xe04b
#define XT_RIGHT 0xe04d
#define XT_DOWN 0xe050
#define XT_NUMLOCK 0x45
#define XT_NUM_DIVIDE 0xe035
#define XT_NUM_MULTIPY 0x57
#define XT_NUM_SUBTRACT 0x4a
#define XT_NUM_ADD 0x4e
#define XT_NUM_ENTER 0xeo1c
#define XT_NUM_INSERT 0x52
#define XT_NUM_DELETE 0x53
#define XT_NUM_UP 0x48
#define XT_NUM_LEFT 0x4b
#define XT_NUM_RIGHT 0x4d
#define XT_NUM_DOWN 0x50
#define XT_NUM_HOME 0x47
#define XT_NUM_END 0x4f
#define XT_NUM_PAGEUP 0x49
#define XT_NUM_PAGEDOWN 0x51

#ifdef __cplusplus
}
#endif

#endif
