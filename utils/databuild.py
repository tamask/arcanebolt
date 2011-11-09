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

def settings_from_manifest_file(path):
    settings = {}
    fp = open(path)
    source = fp.read()
    eval(compile(source, 'manifest.py', 'exec'), {}, settings)
    return settings

def main(argv):
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
        print vars(db)

if __name__ == '__main__':
    main(sys.argv[1:])
