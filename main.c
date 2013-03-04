#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int dmxOpen();
int dmxSend();
int dmxClose();
int dmx_channels[3];

int main(){
	dmx_channels[0] = 255;
	dmx_channels[1] = 255;
	dmx_channels[2] = 255;
	
	if(dmxOpen()){
		printf("Opened\n");
		
		srand(time(NULL));
		
		int i = 0;
		while(i++ < 500){
			
			if(dmxSend(dmx_channels))
				break;
			
			// USB interval is 10 milliseconds
			usleep(10000);
		}
		printf("Send\n");
		
		dmxClose();
		printf("Closed\n");
	}else{
		printf("Couldn't open\n");
	}

	return 0;
}
