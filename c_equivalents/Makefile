NAME = exec
CC = cc
CFLAGS = -Wall -Wextra
RM = rm -rf



SRCS = 	main_c_equivalents.c \
		src/ft_read.c src/ft_strcpy.c src/ft_strlen.c src/ft_write.c src/ft_strcmp.c  src/ft_strdup.c

OBJS = $(SRCS:.c=.o)



all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean:
	@$(RM) $(OBJS) $(NAME)

re: fclean clean all

