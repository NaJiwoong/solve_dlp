all: dlp output.txt

dlp: dlp.c dlp.h mod.c mod.h main.c matrix.c matrix.h
	@rm -f *.o dlp output.txt
	@gcc -o dlp main.c dlp.c dlp.h mod.c mod.h matrix.c matrix.h  -lm

output.txt:
	@./dlp
	@rm -f *.o dlp

clean:
	@rm -f *.o dlp output.txt
