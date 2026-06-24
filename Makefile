NAME        = libasm.a

NCC			= nasm
ASMFLAGS	= -f elf64 -Iinc/

CC			= gcc
CFLAGS		= -Wall -Wextra

AR			= ar rcs
RM			= rm -f


STD_SRCS	= src/ft_strlen.s \
			  src/ft_strcpy.s \
			  src/ft_strcmp.s \
			  src/ft_write.s	\
			  src/ft_read.s \
			  src/ft_strdup.s \
			  src/ft_atoi_base.s \
			  src/ft_list_push_front.s \
			  src/ft_list_size.s \
			  src/ft_list_sort.s \
			  src/ft_list_remove_if.s

STD_OBJS    = $(STD_SRCS:.s=.o)

STD_MAIN	= tests/main.c
STD_TEST	= exec_tests

all: $(NAME)

$(NAME): $(STD_OBJS)
	$(AR) $(NAME) $(STD_OBJS)

%.o: %.s
	$(NCC) $(ASMFLAGS) -o $@ $<

test: $(NAME)
	$(CC) $(CFLAGS) -o $(STD_TEST) $(STD_MAIN) -L. -lasm

clean:
	$(RM) $(STD_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(STD_TEST) $(BONUS_TEST)

re: fclean all


.PHONY: all clean fclean re test