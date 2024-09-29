CC = gcc
#CFLAGS = -lncurses
# FILES = 

READLINE_LIB = ./libreadline.a
HISTORY_LIB = ./libhistory.a

all: main.o  emacs.o builtin.o
	@gcc  main.o  emacs.o builtin.o -o Yshell -lreadline 

#init.o: init.c init.h
#	@gcc -c init.c

builtin.o: builtin.c builtin.h 
	@gcc -c builtin.c 

emacs.o: emacs.c emacs.h
	@gcc -c emacs.c

#job.o: job.c job.h main.h
#	@gcc -c job.c

main.o:  main.h main.c
	@gcc -c main.c

#printinfo.o: printinfo.c config.h printinfo.h
#	@gcc -c printinfo.c

my_readline.o: fileman.o $(READLINE_LIB)
	$(CC) $(LDFLAGS) -o $@ fileman.o $(READLINE_LIB) $(TERMCAP_LIB)

clean:
	@rm  -f ./*.o ./Yshell