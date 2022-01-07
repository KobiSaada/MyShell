
myshell: shell.c
	gcc shell.c -w -o myshell -std=gnu11 -lm -lpthread
	
.PHONY: clean all
clean:
	rm -f *.o *.a *.so myshell
