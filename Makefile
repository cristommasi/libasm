NAME        = libasm.a

NCC			= nasm
ASMFLAGS	= -f elf64 -Istandard/inc -Ibonus/inc

CC			= gcc
CFLAGS		= -Wall -Wextra

AR			= ar rcs
RM			= rm -f


STD_SRCS	= standard/src/ft_strlen.s \
			  standard/src/ft_strcpy.s \
			  standard/src/ft_strcmp.s \
			  standard/src/ft_write.s	\
			  standard/src/ft_read.s \
			  standard/src/ft_strdup.s

STD_OBJS    = $(STD_SRCS:.s=.o)

STD_MAIN	= standard/main.c
STD_TEST	= std_libasm


SRCS_BONUS	= bonus/src/ft_atoi_base_bonus.s \
			  bonus/src/ft_list_push_front_bonus.s \
			  bonus/src/ft_list_size_bonus.s \
			  bonus/src/ft_list_sort_bonus.s

BONUS_OBJS  = $(SRCS_BONUS:.s=.o)

BONUS_MAIN	= bonus/main_bonus.c
BONUS_TEST	= bonus_libasm

all: $(NAME)

$(NAME): $(STD_OBJS)
	$(AR) $(NAME) $(STD_OBJS)

%.o: %.s
	$(NCC) $(ASMFLAGS) -o $@ $<

test: $(NAME)
	$(CC) $(CFLAGS) -o $(STD_TEST) $(STD_MAIN) -L. -lasm

bonus: $(STD_OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(STD_OBJS) $(BONUS_OBJS)

test_bonus: bonus
	$(CC) $(CFLAGS) -o $(BONUS_TEST) $(BONUS_MAIN) -L. -lasm

clean:
	$(RM) $(STD_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(STD_TEST) $(BONUS_TEST)

re: fclean all


.PHONY: all clean fclean re bonus test test_bonus