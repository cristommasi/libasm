#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

#define RANDOM 1
#define NOT_RANDOM 0

typedef struct s_list
{
    void *data;
    struct s_list *next;

}               t_list;

extern int ft_atoi_base(char *str, char *base);
extern void ft_list_push_front(t_list **begin_list, void *data);
extern int ft_list_size(t_list **begin_list);
extern void ft_list_sort(t_list **begin_list, int (*cmp)());
extern void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

size_t      random_number(void) {

    return (rand() % 200);  // range: -100 to 99
}

size_t  **create_arr(size_t len, int random) {

    size_t **arr = malloc(sizeof(size_t *) * len);
    for (size_t i = 0; i < len; i++) {
        arr[i] = malloc(sizeof(size_t));
        if (random)
            *arr[i] = random_number();
        else
            *arr[i] = i;
    }
    return (arr);
}

t_list      **create_list(size_t len, int random) {

    t_list  **begin_list = malloc(sizeof(t_list *));
    *begin_list = NULL;
    size_t  **arr = create_arr(len, random);

    for (size_t i = 0; i < len; i++) {

        ft_list_push_front(begin_list, arr[i]);
    }
    return (begin_list);
}

void        print_list(t_list **begin_list) {

    t_list *cur = *begin_list;
    printf("[%zu] -> ", *(size_t *)cur->data);
    cur = cur->next;
    while (cur) {

        printf("[%zu] -> ", *(size_t *)cur->data);
        cur = cur->next;
    }
    printf("[NULL]\n");
}

int         compare(void *a, void *b) {

    return ( *(size_t*)a > *(size_t*)b);

}


void        free_fct(void *data) {
    free(data);
}



void	    test_atoi_base(void)
{
	char *base10 = "0123456789";
	char *base2 = "01";
	char *base8 = "01234567";
	char *base16 = "0123456789abcdef";
	char *base36 = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *base16_upper = "0123456789ABCDEF";

	char *num1 = "";
	char *num2 = "-2147483648";
	char *num3 = "   +42";
	char *num4 = "\t\n\v\f\r-42";
	char *num5 = "+--++42";
	char *num6 = "42abc";
	char *num7 = "101010";
	char *num8 = "2a";
	char *num9 = "7fffffff";
	char *num10 = "-80000000";


	printf("------ atoi & strtol VS ft_atoi_base -------\n\n");

	printf("empty string                     = %d, %d\n", atoi(num1), ft_atoi_base(num1, base10));
	printf("INT_MIN                          = %d, %d\n", atoi(num2), ft_atoi_base(num2, base10));
	printf("spaces + 42                      = %d, %d\n", atoi(num3), ft_atoi_base(num3, base10));
	printf("all whitespace + -42             = %d, %d\n", atoi(num4), ft_atoi_base(num4, base10));
	printf("invalid sign sequence            = %d, %d\n", atoi(num5), ft_atoi_base(num5, base10));
	printf("stop at letters                  = %d, %d\n", atoi(num6), ft_atoi_base(num6, base10));
	printf("binary 101010                    = %d, %d\n", (int)strtol(num7, NULL, 2), ft_atoi_base(num7, base2));
	printf("hex 2a                           = %d, %d\n", (int)strtol(num8, NULL, 16), ft_atoi_base(num8, base16));
	printf("hex max int (lowercase input)    = %d, %d\n", (int)strtol("7fffffff", NULL, 16), ft_atoi_base(num9, base16));
	printf("hex min int (negative style)     = %d, %d\n", (int)strtol("-80000000", NULL, 16), ft_atoi_base(num10, base16));
    printf("octal 52                         = %d, %d\n", (int)strtol("52", NULL, 8), ft_atoi_base("52", base8));
    printf("octal max int                    = %d, %d\n", (int)strtol("17777777777", NULL, 8), ft_atoi_base("17777777777", base8));
    printf("octal zero                       = %d, %d\n", (int)strtol("0", NULL, 8), ft_atoi_base("0", base8));
    printf("octal invalid stops at 8         = %d, %d\n", (int)strtol("12345877", NULL, 8), ft_atoi_base("12345877", base8));
    printf("base36 16                        = %d, %d\n", (int)strtol("16", NULL, 36), ft_atoi_base("16", base36));
    printf("base36 z                         = %d, %d\n", (int)strtol("z", NULL, 36), ft_atoi_base("z", base36));
    printf("base36 10z                       = %d, %d\n", (int)strtol("10z", NULL, 36), ft_atoi_base("10z", base36));
    printf("base36 big number                = %d, %d\n", (int)strtol("1z141z3", NULL, 36), ft_atoi_base("1z141z3", base36));
    printf("null base                        = %d\n", ft_atoi_base("42", NULL));
    printf("empty base                       = %d\n", ft_atoi_base("42", ""));
    printf("single char base                 = %d\n", ft_atoi_base("42", "0"));
    printf("duplicate in base                = %d\n", ft_atoi_base("42", "0012345678"));
    printf("base contains +                  = %d\n", ft_atoi_base("42", "0123456789+"));
    printf("base contains -                  = %d\n", ft_atoi_base("42", "0123456789-"));
    printf("base contains space              = %d\n", ft_atoi_base("42", "0123456789 "));
    printf("hex upper 2A                     = %d, %d\n", (int)strtol("2A", NULL, 16), ft_atoi_base("2A", base16_upper));
    printf("overflow positive                = %d, %d\n", atoi("2147483648"),  ft_atoi_base("2147483648",  base10));
    printf("overflow large                   = %d, %d\n", atoi("9999999999"),  ft_atoi_base("9999999999",  base10));
    printf("underflow                        = %d, %d\n", atoi("-2147483649"), ft_atoi_base("-2147483649", base10));
    printf("way overflow                     = %d, %d\n", atoi("99999999999999999999"), ft_atoi_base("99999999999999999999", base10));
    printf("just plus                        = %d, %d\n", atoi("+"),           ft_atoi_base("+",           base10));
    printf("just minus                       = %d, %d\n", atoi("-"),           ft_atoi_base("-",           base10));
    printf("plus zero                        = %d, %d\n", atoi("+0"),          ft_atoi_base("+0",          base10));
    printf("minus zero                       = %d, %d\n", atoi("-0"),          ft_atoi_base("-0",          base10));
    printf("double minus                     = %d, %d\n", atoi("--42"),        ft_atoi_base("--42",        base10));
    printf("only whitespace                  = %d, %d\n", atoi("     "),       ft_atoi_base("     ",       base10));
    printf("whitespace after digits          = %d, %d\n", atoi("42   "),       ft_atoi_base("42   ",       base10)); // should stop at space
    printf("whitespace between digits        = %d, %d\n", atoi("4 2"),         ft_atoi_base("4 2",         base10)); // should give 4
    printf("all zeros                        = %d, %d\n", atoi("000000"),      ft_atoi_base("000000",      base10));
    printf("leading zeros                    = %d, %d\n", atoi("007"),         ft_atoi_base("007",         base10));
    printf("negative leading zeros           = %d, %d\n", atoi("-007"),        ft_atoi_base("-007",        base10));
    printf("binary all ones 32bit            = %d, %d\n", (int)strtol("11111111111111111111111111111111", NULL, 2), ft_atoi_base("11111111111111111111111111111111", base2));
    printf("binary invalid char              = %d, %d\n", (int)strtol("1012", NULL, 2), ft_atoi_base("1012", base2)); // stops at '2'
    printf("no valid digits at all           = %d, %d\n", atoi("abc"),         ft_atoi_base("abc",         base10)); // should return 0
    printf("sign then invalid                = %d, %d\n", atoi("+abc"),        ft_atoi_base("+abc",        base10)); // should return 0

}

void        test_list_push_front(void) {

    printf("------ ft_list_push_front -------\n\n");

    t_list  *list = NULL, **begin_list = &list;
    size_t  **data_arr = create_arr(8, NOT_RANDOM);

    
    printf("\nt_list  **begin_list = %p, NULL;  \n", *begin_list);
    for (size_t i = 0; i < 8; i++) {
        *data_arr[i] = i;
        ft_list_push_front(begin_list, data_arr[i]);
    }
    printf("ft_list_push_front()  = ");
    print_list(begin_list);


    t_list  *list2 = malloc(sizeof(t_list));
    size_t data = 69;
    list2->data = &data;
    t_list **begin_list2 = malloc(sizeof(t_list*));
    *begin_list2 = list2;
    size_t  **data_arr2 = create_arr(8, RANDOM);

    printf("\nt_list  **begin_list2 = %p, %zu;  \n", begin_list2, *(size_t*)list2->data);
    for (size_t i = 0; i < 8; i++) {
        *data_arr2[i] = i;
        ft_list_push_front(begin_list2, data_arr2[i]);
    }
    printf("ft_list_push_front()  = ");
    print_list(begin_list2);
    printf("\n");
}

void        test_list_size(void) {

    printf("------ ft_list_size -------\n\n");

    t_list  **begin_list = create_list(8, RANDOM);
    print_list(begin_list);
    printf("ft_list_size()  = %d\n", ft_list_size(begin_list));

    printf("\n");
}

void        test_list_sort(void) {

    printf("------ ft_list_sort -------\n\n");
    t_list  **begin_list = create_list(8, RANDOM);

    printf("begin_list     = ");
    print_list(begin_list);
    ft_list_sort(begin_list, &compare);
    printf("ft_list_sort() = ");
    print_list(begin_list);
}

void        test_list_remove_if(void) {

    printf("------ ft_list_remove_if -------\n\n");

    t_list  **begin_list = create_list(16, RANDOM);
    size_t    data_ref = 115;


    printf("begin_list          = ");
    ft_list_sort(begin_list, &compare);
    print_list(begin_list);

    
    ft_list_remove_if(begin_list, &data_ref, &compare, &free_fct);

    printf("ft_list_remove_if() = ");
    print_list(begin_list);
}

int	main(void)
{

	// test_atoi_base();
    // test_list_push_front();
    // test_list_size();
    // test_list_sort();
    test_list_remove_if();
	return (0);
}
