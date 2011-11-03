import sys
import cStringIO
from PIL import Image

def convert_to_images(data_path, palette_path):
    palette = []
    colors = []
    after_header = False
    with open(palette_path) as data:
        for line in data:
            if line.startswith('#'):
                after_header = True
                continue
            if after_header:
                palette.append(int(line.split()[-1], 2))
                colors.extend(int(i) for i in line.strip().split()[0:3])

    with open(data_path) as data:
        raw = ''
        byte_count = 0
        image_count = 0
        for byte in data.read():
            n = ord(byte)
            if n == 255:
                raw = ''
                byte_count = 0
                image_count += 1
            else:
                raw += chr(palette.index(n))
                byte_count += 1

            if byte_count == 1024:
                im = Image.fromstring('P', (32, 32), raw)
                im.putpalette(colors)
                im_name = data_path + '_%03i.png' % image_count
                im.save(im_name)
                print im_name

def main(argv):
    convert_to_images(argv[0], argv[1])

if __name__ == '__main__':
    main(sys.argv[1:])
