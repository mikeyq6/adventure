CC=gcc -std=c17 -pedantic
OBJS=utils.c adventure.c
LFLAGS=
SUPPRESS=

debug:
	${CC} -g -Wall ${SUPPRESS} ${LFLAGS} -o adventure ${OBJS}

release:
	${CC} -Wall ${SUPPRESS} ${LFLAGS} -o adventure ${OBJS}

clean:
	rm -rf adventure *.o