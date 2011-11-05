#include "track.h"

void
track_init (void)
{
  track_enabled = 0;
  track_channel_mask = TRACK_CHANNEL_HSYNC | TRACK_CHANNEL_VSYNC;
  track_time = 0;
  track_index = 0;
  track_cursor = 0;
  track_offset = 0;
  track_length = 0;
  track_line.time = 1000;
  track_line.hsync = -1;
  track_line.vsync = -1;
}

int
_track_load (int i) {
  if (i < track_count)
    {
      track_index = i;
      track_cursor = 0;
      track_offset = track_size[i][0];
      track_length = track_size[i][1];

      memcpy_P (&track_line, track_data + (track_offset * 3), sizeof (prog_int16_t) * 3);
      
      return 0;
    }
  else
    return 1;
}

int
_track_update (void)
{
  if (vga_time - track_time > (unsigned long)track_line.time * 1000)
    {
      track_time = vga_time;
      track_cursor++;
      if (track_cursor == track_length)
        track_cursor = 0;

      memcpy_P (
        &track_line,
        track_data + ((track_offset + (track_cursor % track_length)) * 3),
        sizeof (prog_int16_t) * 3
      );

      if (track_line.hsync > -1)
        {
          TRACK_ENABLE_CHANNEL (TRACK_CHANNEL_HSYNC);
          VGA_SET_HSYNC (track_line.hsync);
        }
      else
        TRACK_DISABLE_CHANNEL (TRACK_CHANNEL_HSYNC);

      if (track_line.vsync > -1)
        {
          TRACK_ENABLE_CHANNEL (TRACK_CHANNEL_VSYNC);
          VGA_SET_VSYNC (track_line.vsync);
        }
      else
          TRACK_DISABLE_CHANNEL (TRACK_CHANNEL_VSYNC);

      return 1;
    }
  return 0;
}
