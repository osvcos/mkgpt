INCLUDE          := include
MKGPT_OBJECTS    := device.o mkgpt.o mbr.o gpt.o guid.o endian.o utils.o
GPTDUMP_OBJECTS  := gptdump.o device.o endian.o
CFLAGS           := -I$(INCLUDE)
LDFLAGS          := $(shell pkg-config --libs zlib)

all: $(MKGPT_OBJECTS)
	gcc $(MKGPT_OBJECTS) $(LDFLAGS) -o mkgpt

gptdump: $(GPTDUMP_OBJECTS)
	gcc $(GPTDUMP_OBJECTS) -o gptdump

device.o: device.c $(INCLUDE)/device.h
	gcc $(CFLAGS) -c device.c

mkgpt.o: mkgpt.c
	gcc $(CFLAGS) -c mkgpt.c

utils.o: utils.c $(INCLUDE)/utils.h
	gcc $(CFLAGS) -c utils.c

endian.o : endian.c $(INCLUDE)/endian.h
	gcc $(CFLAGS) -c endian.c

guid.o: guid.c $(INCLUDE)/guid.h
	gcc $(CFLAGS) -c guid.c

mbr.o: mbr.c $(INCLUDE)/mbr.h
	gcc $(CFLAGS) -c mbr.c

gpt.o: gpt.c $(INCLUDE)/gpt.h
	gcc $(CFLAGS) -c gpt.c

gptdump.o: gptdump.c
	gcc $(CFLAGS) -c gptdump.c

clean:
	@rm -rf mkgpt gptdump *.o
