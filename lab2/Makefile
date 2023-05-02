test: main.o APIG23.o abb.o APIParte2.o testing.o
	gcc -g -Wall -DNDEBUG -O3 -std=c99 main.o APIG23.o APIParte2.o abb.o testing.o -o test

main.o:
	gcc -g -Wall -DNDEBUG -O3 -std=c99  -c main.c

APIG23.o:
	gcc -g -Wall -DNDEBUG -O3 -std=c99 -c APIG23.c

APIParte2.o:
	gcc -g -Wall -DNDEBUG -O3 -std=c99 -c APIParte2.c

abb.o:
	gcc -g -Wall -DNDEBUG2 -O3 -std=c99 -c abb.c

testing.o:
	gcc -g -Wall -DNDEBUG -O3 -std=c99 -c testing.c

clean:
	rm *.o test *.txt
