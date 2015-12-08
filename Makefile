NAME    := sish
TARBALL := $(NAME).tar

SRC     := sish.c arguments.c
HEADERS :=        arguments.h
FILES   := Makefile README.md $(SRC) $(HEADERS)

CFLAGS      := -Wall -Werror -g
OBJ         := $(SRC:.c=.o)
LINK_LINUX  := -lm -lbsd
LINK_NETBSD := -lm

RM      := rm -f


all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LINK_LINUX) $(CFLAGS)


netbsd: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LINK_NETBSD) $(CFLAGS)


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
