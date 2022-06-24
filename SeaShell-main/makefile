CC = gcc

CFLAGS = -g -Wall

seashell: shell.o utils.o parse.o cd.o echo.o signals.o pipe.o redirection.o helper.o
	${CC} -o seashell ${CFLAGS} shell.o utils.o parse.o cd.o echo.o signals.o pipe.o redirection.o helper.o

clean:
	rm -rf *.o seashell

# Following commands are invoked indirectly.

shell.o: shell.c shell.h
	${CC} ${CFLAGS} -c shell.c

utils.o: utils.c utils.h
	${CC} ${CFLAGS} -c utils.c

parse.o: parse.c parse.h
	${CC} ${CFLAGS} -c parse.c

cd.o: cd.c cd.h
	${CC} ${CFLAGS} -c cd.c

echo.o: echo.c echo.h
	${CC} ${CFLAGS} -c echo.c

signals.o: signals.c signals.h
	${CC} ${CFLAGS} -c signals.c

pipe.o: pipe.c pipe.h
	${CC} ${CFLAGS} -c pipe.c

redirection.o: redirection.c redirection.h
	${CC} ${CFLAGS} -c redirection.c

helper.o: helper.c helper.h
	${CC} ${CFLAGS} -c helper.c
