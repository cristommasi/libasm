NAME = exec
CC = cc
CFLAGS = -Wall -Wextra
RM = rm -rf



SRCS = 	main_c_equivalents.c \
		ft_read.c ft_strcpy.c ft_strlen.c ft_write.c ft_strcmp.c  ft_strdup.c
#  ft_list_sort.c     
# ft_atoi_base.c ft_list_size.c ft_list_push_front.c  
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

