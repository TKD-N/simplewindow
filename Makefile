CC=gcc
CFLAGS="-Wall"
COPT="-lX11"

SRC=    main.c \
        SimpleWindowColorLib.c
 
debug:clean
	$(CC) $(CFLAGS) -g -o simplewindow $(SRC) $(COPT)
stable:clean
	$(CC) $(CFLAGS) -o simplewindow $(SRC) $(COPT)
clean:
	rm -vfr *~ simplewindow
