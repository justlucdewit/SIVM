cc = gcc
bi_sources = bytecode-interpreter/src/main.c
as_sources = assembler/src/main.c

all: sivm sias

sivm:
	rm -f builds/sivm
	$(cc) $(bi_sources) -o builds/sivm

sias:
	rm -f builds/sias
	$(cc) $(as_sources) -o builds/sias