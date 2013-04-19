DMXTest: main.c libdmx.a
	gcc `pkg-config --cflags --libs gtk+-3.0` -Wall main.c -L. -ldmx -lusb -g -o main
