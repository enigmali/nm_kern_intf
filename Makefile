ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
include Kbuild

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

endif

install:
	$(MAKE) -C $(KDIR) M=$$PWD modules_install

clean:
	rm *.o *.ko .*.cmd *.mod.c
