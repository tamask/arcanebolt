import sys

from PIL import Image

def palette_colors(fp, palette_path):
    palette = []
    
    after_header = False
    with open(palette_path) as data:
        for line in data:
            if line.startswith('#'):
                after_header = True
                continue
            if after_header:
                palette.append(int(line.split()[-1], 2))

    palette_str = ''
    for color in palette:
        palette_str += '\\x%x' % color

    print palette_str

if __name__ == '__main__':
    palette_colors(sys.stdout, sys.argv[1])
