BINARY_NAME=chess
FILES=	main.c\
		log.c\
		screen.c\
		select.c\
		network.c

all:
	gcc -o $(BINARY_NAME) $(FILES)

clean:
	del /f $(BINARY_NAME).exe