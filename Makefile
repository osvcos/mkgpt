all: device.o mkgpt.o
	gcc device.o mkgpt.o -o mkgpt

device.o: device.c
	gcc -c device.c

mkgpt.o: mkgpt.c
	gcc -c mkgpt.c

clean:
	@rm -rf mkgpt *.o
