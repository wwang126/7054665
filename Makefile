CC=gcc
CFLAGS=-g -Wall 

all:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}

room:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}

clean:
	rm wwang126.buildrooms
