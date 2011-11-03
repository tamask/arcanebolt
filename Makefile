# arduino v0016
# NOTE: arduino/WInterrupts.c:197-200 disabled

ARDUINO_DIR = arduino
TARGET = main
MCU = atmega328p
F_CPU = 16000000
ARDUINO_PORT = /dev/ttyUSB*
ARDUINO_BAUD = 57600
AVR_TOOLS_PATH = /usr/bin
AVRDUDE = $(ARDUINO_DIR)/hardware/tools/avrdude
AVRDUDE_CONF = $(ARDUINO_DIR)/hardware/tools/avrdude.conf
LOCAL_DEPS = ./build/data.o

include Makefile.in

./build/data.o: $(OBJDIR) ./images/0*.png ./cycles/0*.png
	python ./utils/make_data.py ./utils/palette.gpl ./images/0*.png ./cycles/0*.png > $(OBJDIR)/data.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(OBJDIR)/data.c -o $(OBJDIR)/data.o
