CFLAGS = -Wall -g -pedantic

tg040: tg040.o
	gcc -o tg040 tg040.o

tg040.o: tg040.c
	gcc $(CFLAGS) -c tg040.c

zip: clean
	zip ProjetoSO-Final.zip *

clean:
	rm *.o *.zip tg040
