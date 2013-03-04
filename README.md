USB to DMX driver for Velleman VM116/K8062 on Linux.
------------
How to install:

1. Make the static library using the makefile in the folder Library.
2. Create a program with the following layout and compile it with: `-static -Wall -L. -ldmx`

```c
int dmxOpen();
int dmxSend();
int dmxClose();
int dmx_channels[512];
```

3. Always use `dmxOpen` before using `dmxSend`, and always use `dmxClose` after.
4. You can change the `dmx_channels` to values from 0-255.
