test:test.c comm.c
	gcc -o test test.c comm.c
.PHONY:clean
clean:
	rm -rf test
