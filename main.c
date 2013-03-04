#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <jack/jack.h>

int dmxOpen();
int dmxSend();
int dmxClose();
int dmx_channels[3];

jack_port_t* input_port;
jack_port_t* output_port;

int process(jack_nframes_t nframes, void *arg){
	jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
	jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (input_port, nframes);

	memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);
	
	return 0;
}

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
