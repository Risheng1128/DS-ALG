CC = gcc
default : chess.o function.o chess clean
chess : chess.o function.o
	$(CC) -o chess chess.c function.c stack.c -lev
chess.o : chess.c
	$(CC) -g -Wall -c chess.c -o chess.o
function.o : function.c
	$(CC) -g -Wall -c function.c -o function.o
clean :
	@rm *.o
