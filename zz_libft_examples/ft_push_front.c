typedef struct s_list
{
    void *data;
    struct s_list *next;
} t_list;

void	_ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}