test: main.o APIG23.o abb.o APIParte2.o
	gcc -Wall -DNDEBUG -O3 -std=c99 main.o APIG23.o APIParte2.o abb.o -o test

main.o:
	gcc -Wall -DNDEBUG -O3 -std=c99  -c main.c

APIG23.o:
	gcc -Wall -DNDEBUG -O3 -std=c99 -c APIG23.c

APIParte2.o:
	gcc -Wall -DNDEBUG -O3 -std=c99 -c APIParte2.c

abb.o:
	gcc -Wall -DNDEBUG2 -O3 -std=c99 -c abb.c

clean:
	rm *.o test
