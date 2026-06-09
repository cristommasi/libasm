
NAME        = libasm.a

NCC			= nasm
ASMFLAGS	= -f elf64
CC			= gcc
CFLAGS		= -Wall -Wextra
RM			= rm -f


SRCS    	=	src/ft_strlen.s \
				src/ft_strcpy.s \
				src/ft_strcmp.s \
				src/ft_write.s	\
				src/ft_read.s

SRCS_BONUS	=	bonus/ft_atoi_base_bonus.s

OBJS    	= $(SRCS:.s=.o)
OBJS_BONUS  = $(SRCS_BONUS:.s=.o)


TEST		= test_libasm
TEST_BONUS	= test_libasm_bonus


all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(NCC) $(ASMFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all


test: $(NAME)
	$(CC) $(CFLAGS) -o $(TEST) main.c -L. -lasm


bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

test_bonus: bonus
	gcc $(CFLAGS) -L. -lasm -o $(TEST_BONUS) main_bonus.c



.PHONY: clean fclean re