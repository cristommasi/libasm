typedef struct s_list
{
    void *data;
    struct s_list *next;
} t_list;


void	_ft_list_remove_if(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}