NAME    := sish
TARBALL := $(NAME).tar

SRC     := sish.c lex.yy.c eval.c cd.c echo.c command.c
HEADERS := sish.h
FILES   := Makefile README.md $(SRC) $(HEADERS)

#CFLAGS        := -Wall -Werror -g
OBJ           := $(SRC:.c=.o)
LINUX_LINKS   := -lm -lbsd  -lreadline
NETBSD_LINKS  := -lm -lreadline

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LINUX_LINKS) #$(CFLAGS)

netbsd: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(NETBSD_LINKS) $(CFLAGS)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core
	-$(RM) lex.yy.c

fclean:	clean
	-$(RM) $(NAME)


re: fclean all

package: fclean
	tar cvzf $(TARBALL) $(FILES)
