CC = gcc
CFLAGS = -g -MMD -Wall -Wshadow
EXEC = doom
LIBS = 
OBJECTS = doom.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} ${CFLAGS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

