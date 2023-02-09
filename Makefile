CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
BONUS = pipex_bonus
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

bonus : $(BONUS)

$(BONUS) : $(BFILE)
	$(CC) $(CFLAGS) $(BFILE) -o $(BONUS)

clean:
	$(RM) $(OFILE)

fclean : clean
	$(RM) $(NAME)

re : fclean all
