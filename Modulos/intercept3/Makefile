obj-m := intercept.o
KDIR := /lib/modules//$(shell uname -r)/build
PWD := `pwd`

default:
	make -C $(KDIR) M=$(PWD) modules
	
clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
