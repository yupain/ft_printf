SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_isdigit.c \
	   ft_tolower.c ft_toupper.c ft_isascii.c ft_isalpha.c ft_isalnum.c \
	   ft_isprint.c ft_strlen.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	   ft_strchr.c ft_strrchr.c ft_strncmp.c ft_atoi.c ft_strdup.c \
	   ft_strnstr.c ft_calloc.c ft_strlcpy.c ft_strlcat.c ft_substr.c \
	   ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putnbr_fd.c \
	   ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_utoa.c ft_itoa_hex.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

NAME = libft.a

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -c $(SRCS)
			ar rc $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(OBJS)
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
