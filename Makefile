CFLAGS := -Iinclude
LDFLAGS := $(shell pkg-config --libs zlib)

all: device.o mkgpt.o mbr.o gpt.o
	gcc $(LDFLAGS) device.o mkgpt.o mbr.o gpt.o -o mkgpt

device.o: device.c
	gcc $(CFLAGS) -c device.c

mkgpt.o: mkgpt.c
	gcc $(CFLAGS) -c mkgpt.c

mbr.o: mbr.c
	gcc $(CFLAGS) -c mbr.c

gpt.o: gpt.c
	gcc $(CFLAGS) -c gpt.c

clean:
	@rm -rf mkgpt *.o
