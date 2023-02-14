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

BFILE = pipex_bonus.c \
		uti_bonus.c \
		libft_bonus.c \
		ft_split_bonus.c \

OBONUS = pipex_bonus.o \
		 uti_bonus.o \
		 libft_bonus.o \
		 ft_split_bonus.o \

all : $(NAME)

$(NAME) : $(OFILE)
	$(CC) $(CFLAGS) $(OFILE) -o $(NAME)

bonus : $(BONUS)

$(BONUS) : $(OBONUS)
	cc -fsanitize=address -g $(CFLAGS) $(OBONUS) -o $(BONUS)

clean:
	$(RM) $(OFILE) $(OBONUS)

fclean : clean
	$(RM) $(NAME) $(BONUS)

re : fclean all
