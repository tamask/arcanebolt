#ifndef _INPUT_H
#define _INPUT_H

#include "xt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_BUFFER_LENGTH 16

#define INPUT_RESET() (input_init ())

#define INPUT_CLEAR() (input_clear ())

#define INPUT_WRITE(v) (input_write (v))

#define INPUT_READY() (!input_partial)

#define INPUT_PARSE_INTEGER(v) (input_parse_integer (v))

#define INPUT_SET_INTEGER(v) (input_buffer_number = (v))

#define INPUT_GET_INTEGER() (input_buffer_number)

char input_cursor;
char input_partial;
unsigned int input_buffer[INPUT_BUFFER_LENGTH];
int input_buffer_number;

void input_init ();

void input_clear ();

int input_write (unsigned int symbol);

int input_parse_integer (int *number);

#ifdef __cplusplus
}
#endif

#endif
