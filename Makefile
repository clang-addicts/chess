BINARY_NAME=chess
FLAGS=-lws2_32
FILES=	main.c\
		log.c\
		screen.c\
		select.c\
		network.c\
		game.c

all:
	gcc -o $(BINARY_NAME) $(FILES) $(FLAGS)

clean:
	del /f $(BINARY_NAME).exe