CFLAGS = -Wall -g -pedantic

Main: main.o
	gcc -o Main main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

zip: clean
	zip ProjetoSO-Final.zip *

clean:
	rm *.o Main