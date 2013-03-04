DMXTest: main.c libdmx.a
	gcc -static -Wall main.c -L. -ldmx -lusb -ljack -lpthread -ldl -lrt -g -o main
