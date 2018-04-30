obj-m += hello.o

all: app hello.o app
	
app:
	gcc -Wall -o app app.c

hello.o:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
