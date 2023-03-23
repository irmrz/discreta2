test: main.o APIG23.o
	gcc -Wall -Wextra -O3 -std=c99 main.o APIG23.o -o test

main.o:
	gcc -Wall -Wextra -O3 -std=c99  -c main.c

APIG23.o:
	gcc -Wall -Wextra -O3 -std=c99 -c APIG23.c

clean:
	rm *.o test
