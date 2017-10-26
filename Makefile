CC=gcc
CFLAGS=-g -Wall

all:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}
	${CC} wwang126.adventure.c -o wwang126.adventure ${CFLAGS}

room:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}

roomTest:
	${CC} wwang126.buildrooms.c -o wwang126.buildrooms ${CFLAGS}
	./wwang126.buildrooms

adventure:
	${CC} wwang126.adventure.c -o wwang126.adventure ${CFLAGS} -lpthread

clean:
	rm wwang126.buildrooms
	rm -r wwang126.rooms.*
	rm wwang126.adventure
