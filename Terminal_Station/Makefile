all: pstty lector terminal
pstty: pstty.c
	gcc -o pstty pstty.c
lector: lector.c
	gcc -o lector lector.c
terminal:	terminal.c
	gcc -o terminal terminal.c
clean: pstty lector terminal
	rm pstty && rm lector && rm terminal
