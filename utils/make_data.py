import sys

from PIL import Image

TRACK_LINE_SIZE = 3

def prog_image(fp, palette_path, *data_paths):
    palette = []
    image_sizes = []
    track_sizes = []
    total_images = 0
    total_cycles = 0
    total_tracks = 0
    total_size = 0
    cycle_data = []
    track_data = []

    after_header = False
    with open(palette_path) as data:
        for line in data:
            if line.startswith('#'):
                after_header = True
                continue
            if after_header:
                palette.append(int(line.split()[-1], 2))

    image_sizes = []

    fp.write('#include "data.h"\n\n');

    for idx, image_path in enumerate(data_paths):
        if image_path.startswith('./images/'):
            sys.stderr.write('image: %s\n' % image_path)
            fp.write('prog_char image_%s[] PROGMEM = "' % idx)
            image = Image.open(image_path)
            image_sizes.append(image.size)
            total_size += 4
            for px in image.getdata():
                fp.write('\\x%x' % palette[px])
                total_size += 1
            fp.write('";\n')
            total_images += 1

    image_variables = ', '.join(['image_%s' % n for n in range(total_images)])
    image_size_constructors = ', '.join(['{ %s, %s }' % s for s in image_sizes])
    fp.write('prog_uint16_t image_size[][2] PROGMEM = { %s };\n' % image_size_constructors)
    fp.write('const char *image_data[] PROGMEM = { %s };\n' % image_variables)
    fp.write('char image_count = %s;\n' % total_images)

    for idx, image_path in enumerate(data_paths):
        if image_path.startswith('./cycles/'):
            sys.stderr.write('cycle: %s\n' % image_path)
            cycle = [0] * 64
            image = Image.open(image_path)
            keys = list(image.getdata())[:32]
            values = list(image.getdata())[32:]
            for i, px in enumerate(keys):
                key = palette[px]
                if key < 64:
                    cycle[key] = palette[values[i]]
            cycle_data.extend(cycle)
            total_size += 64
            total_cycles += 1

    fp.write('prog_char cycle_data[] PROGMEM = "%s";\n' % ''.join('\\x%x' % i for i in cycle_data))
    fp.write('char cycle_count = %s;\n' % total_cycles)

    for idx, track_path in enumerate(data_paths):
        if track_path.startswith('./tracks/'):
            sys.stderr.write('track: %s\n' % track_path)
            track_source = open(track_path).read()
            track_lines = [line.strip() for line in track_source.strip().split('\n')]
            track_size = 0
            for line in track_lines:
                if line:
                    track_item = [int(x) for x in line.split()][:TRACK_LINE_SIZE]
                    while (len(track_item) < TRACK_LINE_SIZE):
                        track_item.append(-1)
                    track_data.extend(track_item)
                    track_size += 1
            track_sizes.append((sum(x[1] for x in track_sizes), track_size))
            total_tracks += 1

    fp.write('char track_count = %s;\n' % total_tracks)
    fp.write('unsigned short int track_size[][2] = {%s};\n' % ','.join(str('{%i,%i}' % i) for i in track_sizes))
    fp.write('prog_int16_t track_data[] PROGMEM = {%s};\n' % ','.join(str(i) for i in track_data))

    # space taken by image_table, image_size
    total_size += total_images * 4 * 2
    sys.stderr.write('%s bytes\n' % total_size)
        
if __name__ == '__main__':
    prog_image(sys.stdout, sys.argv[1], *sys.argv[2:])
