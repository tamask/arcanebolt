# arduino v0016
# NOTE: arduino/WInterrupts.c:197-200 disabled

# add a Makefile.local file that defines:
# - AVR_TOOLS_PATH (i.e) /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/
# - ARDUINO_PORT (i.e) /dev/tty.usbmodem*

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

./build/data.o: $(OBJDIR) ./images/0*.png ./cycles/0*.png
	python ./utils/make_data.py ./utils/palette.gpl ./images/0*.png ./cycles/0*.png > $(OBJDIR)/data.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(OBJDIR)/data.c -o $(OBJDIR)/data.o
