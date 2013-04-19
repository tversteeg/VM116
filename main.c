#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define NUM_SLIDERS (6)

struct sliderInfo{
	int* channel_ptr;
	GtkWidget* slider;
};

int dmxOpen();
int dmxSend();
int dmxClose();
int dmx_channels[NUM_SLIDERS];

void setChannel(GtkWidget* widget, struct sliderInfo* data){
	*data->channel_ptr = (int)gtk_range_get_value(GTK_RANGE(data->slider));
}

static gboolean sendData(gpointer data){
	
	if(dmxSend(dmx_channels)){
		dmxClose();
		printf("NOES");
	}
	
	return TRUE;
}

int main(int argc, char *argv[]){
	int i;
	GtkWidget* window;
	GtkWidget* grid;
	GtkWidget* sliders[NUM_SLIDERS];
	
	if(!dmxOpen())
		goto error;
		
	g_thread_init(NULL);	
	gdk_threads_init();
	gdk_threads_enter();
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "DMX Sliders");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);
	
	for(i = 0; i < NUM_SLIDERS; i++){
		sliders[i] = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, 0, 255, 1);
		
		struct sliderInfo* data = malloc(sizeof(*data));
		data->slider = sliders[i];
		data->channel_ptr = &dmx_channels[i];
		
		g_signal_connect(sliders[i], "value-changed", G_CALLBACK(setChannel), data);
		
		if(i == 0){
			gtk_grid_attach (GTK_GRID(grid), sliders[0], 0, 0, 1, 1);
		}else{  
			gtk_grid_attach_next_to (GTK_GRID(grid), sliders[i], sliders[i - 1], GTK_POS_RIGHT, 10, 10);
		}
		gtk_widget_set_size_request(sliders[i], 50, 200);
		gtk_widget_show(sliders[i]);
		
		dmx_channels[i] = 0;
	}
	
	gtk_widget_show(grid);
	gtk_widget_show(window);
	
	gdk_threads_add_timeout(100, sendData, NULL);
	
	gtk_main();
	gdk_threads_leave();
		
	dmxClose();
	return 0;
	
error:
	printf("Error");
	return -1;
}
