NAME    := sish
TARBALL := $(NAME).tar

SRC     := sish.c lex.yy.c eval.c cd.c echo.c command.c
HEADERS := sish.h
FILES   := Makefile README.md $(SRC) $(HEADERS)

CFLAGS  := -Wall -Werror -g
OBJ     := $(SRC:.c=.o)
LINKS   := -lm -lbsd  -lreadline

all: $(OBJ)
	#$(shell lex parser.c)
	$(CC) $(OBJ) -o $(NAME) $(LINKS) $(CFLAGS)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core
	#-$(RM) lex.yy.c

fclean:	clean
	-$(RM) $(NAME)


re: fclean all

package: fclean
	tar cvzf $(TARBALL) $(FILES)
