#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlst;

	newlst = (t_list *) malloc(sizeof(t_list));
	if (!newlst)
		return (0);
	newlst->next = 0;
	newlst->content = content;
	return (newlst);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptrlst;

	if (lst == NULL)
		return (lst);
	ptrlst = lst;
	while (ptrlst->next)
		ptrlst = ptrlst->next;
	return (ptrlst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptrlst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ptrlst = ft_lstlast(*lst);
	ptrlst->next = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst && *lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
		lst = NULL;
	}
}

void	append(t_list **head_ref, void *data)
{
	t_list	*new_node;
	t_list	*last;

	last = *head_ref;
	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->content = (void *)data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return ;
}