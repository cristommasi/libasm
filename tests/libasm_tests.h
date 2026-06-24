#ifndef LIBASM_TESTS_H
#define LIBASM_TEST_H

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

size_t      ft_strlen(char const *s);
char        *ft_strcpy(char *dest, const char *src);
int         ft_strcmp(const char *s1, const char *s2);
ssize_t     ft_write(int fd, const void *buf, size_t count);
ssize_t     ft_read(int fd, void *buf, size_t count);
char        *ft_strdup(char *s);
int         ft_atoi_base(char *str, char *base);
void        ft_list_push_front(t_list **begin_list, void *data);
int         ft_list_size(t_list *begin_list);
void        ft_list_sort(t_list **begin_list, int (*cmp)());
void        ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

int         compare(void *a, void *b);
void        free_fct(void *data);
void        free_fct2(void *data);
void        print_list(t_list **begin_list);
t_list      **create_list(size_t len, int random);
size_t      **create_arr(size_t len, int random);
size_t   **free_arr(size_t **arr, size_t len);
size_t      random_number(void);


inline size_t      random_number(void) {

    return (rand() % 200);
}

inline size_t   **free_arr(size_t **arr, size_t len) {

    for (size_t i = 0; i < len; i++) {
        free(arr[i]);
    }
    free(arr);
    return (arr);
}

inline size_t   **create_arr(size_t len, int random) {

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

inline t_list   **create_list(size_t len, int random) {

    t_list  **begin_list = malloc(sizeof(t_list *));
    *begin_list = NULL;
    size_t  **arr = create_arr(len, random);

    for (size_t i = 0; i < len; i++) {

        ft_list_push_front(begin_list, arr[i]);
    }
    return (begin_list);
}

inline void print_list(t_list **begin_list) {

    if (!begin_list)  {
        printf("[NULL]\n");
        return ;
    }
    t_list *cur = *begin_list;
    if (!cur) {
        printf("[NULL]\n");
        return ;
    }
    printf("[%zu] -> ", *(size_t *)cur->data);
    cur = cur->next;
    while (cur) {

        printf("[%zu] -> ", *(size_t *)cur->data);
        cur = cur->next;
    }
    printf("[NULL]\n");
}

inline int  compare(void *a, void *b) {

    return ( *(size_t*)a > *(size_t*)b);

}

inline void free_fct(void *data) {
    free(data);
}

inline void free_fct2(void *data) {
    return ;
}


#endif