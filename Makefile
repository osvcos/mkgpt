all: device.o mkgpt.o mbr.o gpt.o
	gcc device.o mkgpt.o mbr.o gpt.o -o mkgpt

device.o: device.c
	gcc -c device.c

mkgpt.o: mkgpt.c
	gcc -c mkgpt.c

mbr.o: mbr.c
	gcc -c mbr.c

gpt.o: gpt.c
	gcc -c gpt.c

clean:
	@rm -rf mkgpt *.o
