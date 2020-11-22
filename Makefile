bin_sysbm: main.c
	gcc -pthread -Wall -g -o bin_sysbm main.c
.PHONY: clean
clean:
	-rm bin_sysbm