CC=gcc
CFLAGS=-g -Wall -std=c99

all:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}

room:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}

clean:
