#include <usb.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#include "DMXLib.h"

struct usb_device *dev;
usb_dev_handle *udev;

int writeCommand(unsigned char *data){
	int result = usb_interrupt_write(udev,0x1,(char*)data,8,20);
	if(result < 0){
		perror("Writing to USB failed");
		return 1;
	}else{
		return 0;
	}
}

int dmxOpen(){
	int result;
	
	struct usb_bus *busses;
	struct usb_bus *bus;
	
	usb_init();
	usb_find_busses();
	result = usb_find_devices();
	if(result < 0){
		perror("Finding USB devices failed");
		return 0;
	}
	
	usb_set_debug(1);

	busses = usb_get_busses();
	for(bus = busses; bus; bus = bus->next){
		for(dev = bus->devices; dev; dev = dev->next){
			 if ((dev->descriptor.idVendor == 0x10cf) && (dev->descriptor.idProduct == 0x8062)){
				udev = usb_open(dev);
#if defined(LIBUSB_HAS_GET_DRIVER_NP) && defined(LIBUSB_HAS_DETACH_KERNEL_DRIVER_NP)
				usb_detach_kernel_driver_np(udev, 0);
#endif
				result = usb_set_configuration(udev, dev->descriptor.bNumConfigurations);
				if(result < 0){
					usb_close(udev);
					perror("Configurating USB failed");
					return 0;
				}
				result = usb_claim_interface(udev, 0);
				if(result < 0){
					usb_release_interface(udev, 1);
					usb_close(udev);
					perror("Claiming USB failed");
					return 0;
				}
				return 1;
			}
		}
	}
	return 0;
}

int dmxSend(int* channels){
	int i, n, m;
	unsigned char data[8];

	m = sizeof(channels)/sizeof(channels[0]);
	for(i = 0; (i < 100) && !channels[i] && (i < m - 6); i++);
	
	data[0] = 4;
	data[1] = i + 1;
	data[2] = channels[i];
	data[3] = channels[i + 1];
	data[4] = channels[i + 2];
	data[5] = channels[i + 3];
	data[6] = channels[i + 4];
	data[7] = channels[i + 5];
	
	if(writeCommand(data)) return 1;
	i += 6;

	while(i < m - 7){
		if(!channels[i]){
			for(n = i + 1; (n < m -6) && (n - i < 100) && !channels[n]; n++);
			data[0] = 5;
			data[1] = n - 1;
			data[2] = channels[n];
			data[3] = channels[n + 1];
			data[4] = channels[n + 2];
			data[5] = channels[n + 3];
			data[6] = channels[n + 4];
			data[7] = channels[n + 5];

			if(writeCommand(data)) return 1;
			i = n + 6;		
		}else{
			data[0] = 2;
			data[1] = channels[i];
			data[2] = channels[i + 1];
			data[3] = channels[i + 2];
			data[4] = channels[i + 3];
			data[5] = channels[i + 4];
			data[6] = channels[i + 5];
			data[7] = channels[i + 6];
			if(writeCommand(data)) return 1;
			i += 7;
		}
	}

	for(; i < m; i++){
		data[0] = 3;
		data[1] = channels[i];
		if(writeCommand(data)) return 1;
	}
	return 0;
}

int dmxClose(){
	usb_release_interface(udev, 1);
	usb_close(udev);	
	return 0;
}
