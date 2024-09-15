obj-m := debugfs.o
debugfs-objs := foo.o jiffies.o id.o main.o


PWD = $(shell pwd)
KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

