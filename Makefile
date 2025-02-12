all: pipe3

clean:
	rm -f pipe3

pipe3: pipe3.c
	gcc -o pipe3 pipe3.c -Wall