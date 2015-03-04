TOOLCHAIN=~/toolchain/gcc-arm-none-eabi-4_9-2014q4/bin
PREFIX=$(TOOLCHAIN)/arm-none-eabi-

ARCHFLAGS=-mthumb -mcpu=cortex-m0plus
CFLAGS=-I./includes/
LDFLAGS=--specs=nano.specs -Wl,--gc-sections,-Map,$(TARGET).map,-Tlink.ld

CC=$(PREFIX)gcc
LD=$(PREFIX)gcc
OBJCOPY=$(PREFIX)objcopy
SIZE=$(PREFIX)size
RM=rm -f

TARGET=main

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: build size
build: elf srec
elf: $(TARGET).elf
srec: $(TARGET).srec

clean:
	$(RM) $(TARGET).srec $(TARGET).elf $(TARGET).map $(OBJ)

%.o: %.c
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $@ $<

$(TARGET).elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

%.srec: %.elf
	$(OBJCOPY) -O srec $< $@

size:
	$(SIZE) $(TARGET).elf
