DMXTest: main.c libdmx.a
	gcc -static -Wall main.c -L. -ldmx -lusb -g -o main
