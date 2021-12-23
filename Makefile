
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m   := hello.o
ccflags-y += -g
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello.ko hello.ko.unstripped
	$(CROSS_COMPILE)strip -dS hello.o
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
