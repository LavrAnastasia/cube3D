CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
NAME = libft.a
SOURCES = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strcmp.c \
	ft_split.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_utoa.c \
	ft_printf.c \
	ft_is_array_sorted.c \
	ft_satoi.c \
	ft_decode_bits_to_char.c \
	printf/ft_printf_utils.c \
	printf/ft_print_str.c \
	printf/ft_print_int.c \
	printf/ft_print_uint.c \
	printf/ft_print_char.c \
	printf/ft_print_p.c \
	printf/ft_puthex.c \
	ft_putnbr_fd.c \
	get_next_line/get_next_line.c 
OBJECTS = $(SOURCES:.c=.o)

BONUS_SOURCES = \
	ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c

BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $@ $^

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME) .bonus

re: fclean all

bonus: .bonus

.bonus: $(NAME) $(BONUS_OBJECTS)
	ar rc $(NAME) $(BONUS_OBJECTS)
	touch .bonus

.PHONY: all clean fclean re bonus
