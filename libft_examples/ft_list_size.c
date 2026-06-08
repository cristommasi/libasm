#include <stddef.h>

typedef struct s_list
{
    void *data;
    struct s_list *next;
} t_list;


int	_ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}