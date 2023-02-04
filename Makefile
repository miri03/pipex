CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
RM = rm -rf

CFILE = pipex.c \
		uti.c \
		libft.c \
		ft_split.c \

OFILE = pipex.o \
		uti.o \
		libft.o \
		ft_split.o 

all : $(NAME)

$(NAME) : $(OFILE)
	$(CC) $(CFLAGS) $(OFILE) -o $(NAME)

clean:
	$(RM) $(OFILE)

fclean : clean
	$(RM) $(NAME)

re : fclean all
