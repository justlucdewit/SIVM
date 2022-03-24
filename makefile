cc = gcc
bi_sources = SIVM/src/main.c
as_sources = SIAS/src/main.c
da_sources = SIDA/src/main.c
doc_sources = SIDOC/src/main.c

all: sivm sias sida sidoc

sivm:
	rm -f builds/sivm
	$(cc) $(bi_sources) -o builds/sivm

sias:
	rm -f builds/sias
	$(cc) $(as_sources) -o builds/sias

sida:
	rm -f builds/sida
	$(cc) $(da_sources) -o builds/sida

sidoc:
	rm -f builds/sidoc
	$(cc) $(doc_sources) -o builds/sidoc

cloc:
	onefetch

tst: all
	sias test/test.asm
	# mv output test/output
	# sivm test/output