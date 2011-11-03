import sys
import serial

def main(argv):
    device = argv[0]
    s = serial.Serial(device)
    try:
        while 1:
            sys.stdout.write(s.read())
            sys.stdout.flush()
    except KeyboardInterrupt:
        pass

if __name__ == '__main__':
    main(sys.argv[1:])
