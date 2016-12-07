NAME=dmx

RM=rm -rf
ccflags-y +=-g -Wall

ifneq ($(KERNELRELEASE),)
	obj-m := dmx_driver.o

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm *.symvers
endif
