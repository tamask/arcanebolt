import os
import sys
from PIL import Image

class DataBuilder(object):
    def __init__(self, settings):
        self.settings = settings

    def build(self):
        self.build_palette()
        self.build_images()
        self.build_cycles()
        self.build_tracks()

    def dump(self, o):
        self.dump_images(o)
        self.dump_cycles(o)
        self.dump_tracks(o)

    def build_palette(self):
        palette = []
        source = self.settings['PALETTE']
        after_header = False
        with open(source) as data:
            for line in data:
                if line.startswith('#'):
                    after_header = True
                    continue
                if after_header:
                    palette.append(int(line.split()[-1], 2))
        self.palette = palette

    def build_images(self):
        images = []
        for image_path in self.settings.get('IMAGES', []):
            source = Image.open(image_path)
            data = ''
            size = 0
            for px in source.getdata():
                data += '\\x%x' % self.palette[px]
                size += 1
            images.append({
                'data': data,
                'size': size,
                'dimensions': source.size,
             })
        self.images = images

    def build_cycles(self):
        cycles = []
        for cycle_path in self.settings.get('CYCLES', []):
            source = Image.open(cycle_path)
            cycle = [0] * 64
            keys = list(source.getdata())[:32]
            values = list(source.getdata())[32:]
            for i, px in enumerate(keys):
                key = self.palette[px]
                if key < 64:
                    cycle[key] = self.palette[values[i]]
            cycles.append(cycle)
        self.cycles = cycles

    def build_tracks(self):
        tracks = []
        for track_path in self.settings.get('TRACKS', []):
            track = []
            with open(track_path) as source:
                for line in source:
                    line = line.strip()
                    if line and not line.startswith('#'):
                        values = map(int, line.split())
                        while len(values) < 3:
                            values.append(-1)
                        track.append(tuple(values))
            if track:
                tracks.append(track)
        self.tracks = tracks

    def dump_images(self, o):
        image_count = len(self.images)
        image_sizes = [
            i['dimensions'] for i in self.images]
        image_variables = ','.join(['image_%s' % n for n in range(image_count)])
        image_size_data = ', '.join(['{%s,%s}' % s for s in image_sizes])

        for i, image in enumerate(self.images):
            o.write('prog_char image_%s[] PROGMEM = "%s";\n' % (i, image['data']))
        o.write('prog_uint16_t image_size[][2] PROGMEM = {%s};\n' % image_size_data)
        o.write('const char *image_data[] PROGMEM = {%s};\n' % image_variables)
        o.write('char image_count = %s;\n' % image_count)

    def dump_cycles(self, o):
        cycle_data = []
        total_size = 0
        cycle_count = len(self.cycles)
        for cycle in self.cycles:
            cycle_data.extend(cycle)
            total_size += 64
        cycle_str_data = ''.join('\\x%x' % i for i in cycle_data)

        o.write('prog_char cycle_data[] PROGMEM = "%s";\n' % cycle_str_data)
        o.write('char cycle_count = %s;\n' % cycle_count)

    def dump_tracks(self, o):
        track_data = []
        track_sizes = []
        total_tracks = len(self.tracks)
        for track in self.tracks:
            size = len(track)
            for line in track:
                track_data.extend(line)
            track_sizes.append((sum(x[1] for x in track_sizes), size))
        track_size_data = ','.join(str('{%i,%i}' % i) for i in track_sizes)
        track_data = ','.join(str(i) for i in track_data)

        o.write('char track_count = %s;\n' % total_tracks)
        o.write('unsigned short int track_size[][2] = {%s};\n' % track_size_data)
        o.write('prog_int16_t track_data[] PROGMEM = {%s};\n' % track_data)

def settings_from_manifest_file(path):
    settings = {}
    fp = open(path)
    source = fp.read()
    eval(compile(source, 'manifest.py', 'exec'), {}, settings)
    return settings

def main(argv, out):
    try:
        manifest_file = argv[0]
    except IndexError:
        sys.stderr.write('Manifest file not specified\n')
        sys.exit(1)
    else:
        settings = settings_from_manifest_file(manifest_file)
        os.chdir(os.path.dirname(os.path.realpath(manifest_file)))
        db = DataBuilder(settings)
        db.build()
        db.dump(out)

if __name__ == '__main__':
    main(sys.argv[1:], sys.stdout)
