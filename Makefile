all: device.o mkgpt.o mbr.o
	gcc device.o mkgpt.o mbr.o -o mkgpt

device.o: device.c
	gcc -c device.c

mkgpt.o: mkgpt.c
	gcc -c mkgpt.c

mbr.o: mbr.c
	gcc -c mbr.c

clean:
	@rm -rf mkgpt *.o
