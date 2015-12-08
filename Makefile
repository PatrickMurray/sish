NAME    := sish
TARBALL := $(NAME).tar

SRC     := sish.c arguments.c tokenization.c
HEADERS :=        arguments.h tokenization.h
FILES   := Makefile README.md $(SRC) $(HEADERS)

CFLAGS  := -Wall -Werror -g
OBJ     := $(SRC:.c=.o)
LINKS   := -lm -lbsd

RM      := rm -f


all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LINKS) $(CFLAGS)


clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)


re: fclean all


package: fclean
	tar cvzf $(TARBALL) $(FILES)
