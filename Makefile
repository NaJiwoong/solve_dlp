all: dlp output.txt

dlp: dlp.c dlp.h mod.c mod.h main.c
	@rm -f *.o dlp output.txt
	@gcc -o dlp main.c dlp.c dlp.h mod.c mod.h -lm

output.txt:
	@./dlp
	@rm -f *.o dlp

clean:
	@rm -f *.o dlp output.txt
