# arcanebolt
#
# Install Arduino.app 1.0.6
#
# Latest build/upload process only tested with Arduino Uno
#
# Create a Manifest.json that defines what data to compile:
#   {"images": ["path1.png", "path2.png", ...], "cycles": ["cycle1.png", "cycle2.png", ...]}
#
# Add a Makefile.local file that defines:
#   AVR_TOOLS_PATH (i.e) /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/
#   ARDUINO_PORT (i.e) /dev/tty.usbmodem*
#
# To make new images, import and use the utils/palette.gpl in Gimp.
# Make sure to index the the png image with the palette, and uncheck 'remove unused colors'.
# Images can be any dimension up to max 32x32 pixels.
#
# Using modified arduino v0016:
#   - arduino/WInterrupts.c:197-200 disabled

-include Makefile.local

ARDUINO_DIR = arduino
TARGET = main
MCU = atmega328p
F_CPU = 16000000
AVRDUDE = $(AVR_TOOLS_PATH)/avrdude
AVRDUDE_CONF = $(AVR_TOOLS_PATH)/../etc/avrdude.conf
LOCAL_DEPS = ./build/data.o

include Makefile.in

AVRDUDE_ARD_OPTS = -c arduino -P $(ARDUINO_PORT)

./build/data.o: $(OBJDIR) ./data/images/*.png ./data/cycles/*.png
	python ./utils/make_data.py ./utils/palette.gpl Manifest.json > $(OBJDIR)/data.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(OBJDIR)/data.c -o $(OBJDIR)/data.o
