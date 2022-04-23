BINARY_NAME=chess
FILES=	main.c\
		log.c

all:
	gcc -o $(BINARY_NAME) $(FILES)

clean:
	rm -rf $(BINARY_NAME)