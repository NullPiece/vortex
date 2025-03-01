run :
	gcc -Wall -g main.c -o app `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
	./app.exe