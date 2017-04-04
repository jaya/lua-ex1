all:
	gcc main.c -o main -llua -lm -g3 -O0 -ldl
run:
	./main
