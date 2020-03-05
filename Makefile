CFLAGS := -Iinclude
LDFLAGS := $(shell pkg-config --libs zlib)

all: device.o mkgpt.o mbr.o gpt.o guid.o endian.o
	gcc $(LDFLAGS) device.o mkgpt.o mbr.o gpt.o guid.o endian.o -o mkgpt

gptdump: gptdump.o device.o endian.o
	gcc $(LDFLAGS) gptdump.o device.o endian.o -o gptdump

device.o: device.c
	gcc $(CFLAGS) -c device.c

mkgpt.o: mkgpt.c
	gcc $(CFLAGS) -c mkgpt.c

endian.o : endian.c
	gcc $(CFLAGS) -c endian.c

guid.o: guid.c
	gcc $(CFLAGS) -c guid.c

mbr.o: mbr.c
	gcc $(CFLAGS) -c mbr.c

gpt.o: gpt.c
	gcc $(CFLAGS) -c gpt.c

gptdump.o: gptdump.c
	gcc $(CFLAGS) -c gptdump.c

clean:
	@rm -rf mkgpt gptdump *.o
