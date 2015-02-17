#include "input.h"

void
input_init ()
{
  input_clear ();
  input_buffer_number = 0;
}

void 
input_clear ()
{
  int i;

  for (i = 0; i < INPUT_BUFFER_LENGTH; i++)
    input_buffer[i] = 0;

  input_cursor = 0;
  input_partial = 0;
}

int
input_write (unsigned int symbol)
{
  if (input_cursor == INPUT_BUFFER_LENGTH)
    return 1;

  input_partial = 1;
  input_buffer[input_cursor++] = symbol;

  return 0;
}

int
input_parse_integer (int *number)
{
  int i;
  int sign;
  unsigned int symbol;

  sign = 1;
  if (number == 0)
    number = &input_buffer_number;
  *number = 0;

  for (i = 0; i < INPUT_BUFFER_LENGTH; i++)
    {
      symbol = input_buffer[i];

      if (symbol == XT_MINUS)
        sign = -1;
      else if (symbol > 1 && symbol < 12)
        {
          symbol -= 1;
          symbol %= 10;
          *number *= 10;
          *number += symbol;
        }
    }

  *number *= sign;

  return 0;
}
