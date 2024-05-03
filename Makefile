all: draw
	cc -ggdb main.c draw.o -o main -lraylib -lm
draw:
	cc -ggdb draw.c -c -o draw.o
