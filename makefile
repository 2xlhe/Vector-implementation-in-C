CC = Clang
IN = vector.c
OUT = vector

#FLAGS = -Wall -Wextra -Werror

compile:
	$(CC) $(FLAGS) $(IN) -o $(OUT)

run:
	./$(OUT)

all: compile run
