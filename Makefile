CC = gcc
CFLAGS = -g -MMD -Wall -Wshadow -lncurses
EXEC = doom
LIBS = 
OBJECTS = doom.o element.o misc.o input.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} ${CFLAGS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

